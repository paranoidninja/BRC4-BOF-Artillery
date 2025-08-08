#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <stdlib.h>
#include <string.h>
#include "badger_exports.h"

WINBASEAPI FARPROC WINAPI KERNEL32$GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
WINBASEAPI HMODULE WINAPI KERNEL32$LoadLibraryA(LPCSTR lpLibFileName);
WINBASEAPI BOOL WINAPI KERNEL32$FreeLibrary(HMODULE hLibModule);
WINBASEAPI BOOL WINAPI KERNEL32$LocalFree(HLOCAL hMem);
WINBASEAPI int WINAPI KERNEL32$MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
WINBASEAPI errno_t __cdecl MSVCRT$wcscpy_s(wchar_t *_Dst, rsize_t _DstSize, const wchar_t *_Src);
WINBASEAPI size_t __cdecl MSVCRT$wcstombs(char* _Dest, const wchar_t* _Source, size_t _MaxCount);

// i ripped these structs from https://processhacker.sourceforge.io/doc/winsta_8h_source.html
typedef WCHAR WINSTATIONNAME[32 + 1];
typedef enum _WINSTATIONSTATECLASS {
    State_Active = 0,
    State_Connected,
    State_ConnectQuery,
    State_Shadow,
    State_Disconnected,
    State_Idle,
    State_Listen,
    State_Reset,
    State_Down,
    State_Init
} WINSTATIONSTATECLASS;

typedef struct _SESSIONIDW {
    union {
        ULONG SessionId;
        ULONG LogonId;
    };
    WINSTATIONNAME WinStationName;
    WINSTATIONSTATECLASS State;
} SESSIONIDW, * PSESSIONIDW;

typedef HANDLE(WINAPI* LPFN_WinStationOpenServerW)(PWSTR);
typedef BOOLEAN(WINAPI* LPFN_WinStationCloseServer)(HANDLE);
typedef BOOLEAN(WINAPI* LPFN_WinStationEnumerateW)(HANDLE, PSESSIONIDW*, PULONG);
typedef BOOLEAN(WINAPI* LPFN_WinStationQueryInformationW)(HANDLE, ULONG, WINSTATIONINFOCLASS, PVOID, ULONG, PULONG);

void extractWideStrings(const BYTE* byteArray, size_t size, wchar_t*** strings, size_t* count) {
    size_t i, j = 0;
    size_t stringCount = 0;
    wchar_t* currentString = (wchar_t*)BadgerAlloc(size * sizeof(wchar_t));
    *strings = (wchar_t**)BadgerAlloc(size * sizeof(wchar_t*));

    for (i = 0; i < size / sizeof(WCHAR); ++i) {
        if (byteArray[i * sizeof(WCHAR)] == 0 && BadgerWcslen(currentString) == 0) {
            continue; // Skip null characters at the beginning
        }
        currentString[j++] = (WCHAR)byteArray[i * sizeof(WCHAR)];
        if (byteArray[i * sizeof(WCHAR)] == 0) {
            (*strings)[stringCount] = (wchar_t*)BadgerAlloc((j + 1) * sizeof(wchar_t));
            MSVCRT$wcscpy_s((*strings)[stringCount], j + 1, currentString);
            stringCount++;
            j = 0;
        }
    }

    *count = stringCount;
    BadgerFree((void**)&currentString);
}

void* LoadFunctionFromDLL(HINSTANCE hDLL, const char* functionName) {
    void* functionPtr = (void*)KERNEL32$GetProcAddress(hDLL, functionName);
    if (functionPtr == NULL) {
        KERNEL32$FreeLibrary(hDLL);
        exit(1);
    }
    return functionPtr;
}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    if (argc < 1) {
        BadgerDispatch(dispatch, "%s\n", "[!] Usage: session_enum.o <serverName>");
        return;
    }
    LPSTR pszServerName = argv[0];

    BadgerDispatch(dispatch, "[*] Querying server: '%s'\n", pszServerName);

    int size_needed = KERNEL32$MultiByteToWideChar(CP_UTF8, 0, pszServerName, -1, NULL, 0);
    if (size_needed <= 0) {
        BadgerDispatch(dispatch, "[!] Invalid server name encoding.\n");
        return;
    }

    wchar_t* pwszServerName = (wchar_t*)BadgerAlloc(size_needed * sizeof(wchar_t));
    if (!pwszServerName) {
        BadgerDispatch(dispatch, "[!] Allocation failed.\n");
        return;
    }

    KERNEL32$MultiByteToWideChar(CP_UTF8, 0, pszServerName, -1, pwszServerName, size_needed);

    if (BadgerWcslen(pwszServerName) > 20) {
        BadgerDispatch(dispatch, "[!] Server name exceeds maximum length.\n");
        goto cleanup;
    }

    HINSTANCE hDLL = KERNEL32$LoadLibraryA("winsta.dll");
    if (!hDLL) {
        BadgerDispatch(dispatch, "[!] Failed to load winsta.dll\n");
        goto cleanup;
    }

    LPFN_WinStationOpenServerW pfnWinStationOpenServerW = (LPFN_WinStationOpenServerW)LoadFunctionFromDLL(hDLL, "WinStationOpenServerW");
    LPFN_WinStationCloseServer pfnWinStationCloseServer = (LPFN_WinStationCloseServer)LoadFunctionFromDLL(hDLL, "WinStationCloseServer");
    LPFN_WinStationEnumerateW pfnWinStationEnumerateW = (LPFN_WinStationEnumerateW)LoadFunctionFromDLL(hDLL, "WinStationEnumerateW");
    LPFN_WinStationQueryInformationW pfnWinStationQueryInformationW = (LPFN_WinStationQueryInformationW)LoadFunctionFromDLL(hDLL, "WinStationQueryInformationW");

    if (!pfnWinStationOpenServerW || !pfnWinStationCloseServer || !pfnWinStationEnumerateW || !pfnWinStationQueryInformationW) {
        BadgerDispatch(dispatch, "[!] Failed to resolve one or more functions.\n");
        goto cleanup;
    }

    HANDLE hServer = pfnWinStationOpenServerW(pwszServerName);
    if (!hServer) {
        BadgerDispatch(dispatch, "[!] Failed to open server\n");
        goto cleanup;
    }

    BadgerDispatch(dispatch, "[*] Successfully opened server\n");

    PSESSIONIDW pSessionIds = NULL;
    ULONG count = 0;
    BOOLEAN enumResult = pfnWinStationEnumerateW(hServer, &pSessionIds, &count);

    if (enumResult && pSessionIds) {
        BadgerDispatch(dispatch, "Number of sessions: %lu\n", count);

        for (ULONG i = 0; i < count; i++) {
            char sessionName[33] = {0};
            char userNameStr[256] = "<unknown>";

            MSVCRT$wcstombs(sessionName, pSessionIds[i].WinStationName, 32);
            sessionName[32] = '\0';

            WINSTATIONINFORMATIONW wsInfo;
            ULONG ReturnLen;

            BadgerDispatch(dispatch, "Session ID: %lu\n", pSessionIds[i].SessionId);
            BadgerDispatch(dispatch, "State: %lu\n", pSessionIds[i].State);
            BadgerDispatch(dispatch, "Session Name: %s\n", sessionName);

            if (pfnWinStationQueryInformationW(hServer,
                                               pSessionIds[i].SessionId,
                                               WinStationInformation,
                                               &wsInfo,
                                               sizeof(wsInfo),
                                               &ReturnLen) &&
                (wsInfo.LogonId != 0)) {

                wchar_t** reserved2Strings = NULL;
                wchar_t** reserved3Strings = NULL;
                size_t reserved2Count = 0, reserved3Count = 0;

                extractWideStrings(wsInfo.Reserved2, sizeof(wsInfo.Reserved2), &reserved2Strings, &reserved2Count);
                extractWideStrings(wsInfo.Reserved3, sizeof(wsInfo.Reserved3), &reserved3Strings, &reserved3Count);

                wchar_t* userName = NULL;
                for (size_t j = reserved3Count; j > 0; j--) {
                    if (reserved3Strings[j - 1] && BadgerWcslen(reserved3Strings[j - 1]) > 0) {
                        userName = reserved3Strings[j - 1];
                        break;
                    }
                }

                if (userName) {
                    MSVCRT$wcstombs(userNameStr, userName, sizeof(userNameStr) - 1);
                    userNameStr[sizeof(userNameStr) - 1] = '\0';
                }

                for (size_t j = 0; j < reserved2Count; j++) {
                    BadgerFree((void*)reserved2Strings[j]);
                }
                for (size_t j = 0; j < reserved3Count; j++) {
                    BadgerFree((void*)reserved3Strings[j]);
                }

                BadgerFree((void*)reserved2Strings);
                BadgerFree((void*)reserved3Strings);
            }

            BadgerDispatch(dispatch, "Username: %s\n", userNameStr);
        }

        KERNEL32$LocalFree(pSessionIds);
    } else {
        BadgerDispatch(dispatch, "[!] Failed to enumerate sessions.\n");
    }

    pfnWinStationCloseServer(hServer);

cleanup:
    if (hDLL) KERNEL32$FreeLibrary(hDLL);
    if (pwszServerName) BadgerFree((void*)pwszServerName);
}

