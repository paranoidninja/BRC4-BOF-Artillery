#ifndef DEFINTIIONS_H
#define DEFINTIIONS_H

#include <windows.h>
#include <tlhelp32.h>
#include <winhttp.h>
#include <process.h>
#include <evntprov.h>
#include <stdio.h>
#include <winternl.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <shlobj.h>
#include <errno.h>    
#include <security.h>


// MSVCRT
WINBASEAPI size_t __cdecl MSVCRT$wcslen(const wchar_t *_Str);
WINBASEAPI int __cdecl MSVCRT$vsnprintf(char * __restrict__ d,size_t n,const char * __restrict__ format,va_list arg);
WINBASEAPI errno_t __cdecl MSVCRT$mbstowcs_s(size_t *pReturnValue, wchar_t * wcstr, size_t smt,const char *mbstr, size_t count);
WINBASEAPI size_t __cdecl MSVCRT$strnlen(const char *_Str, size_t _MaxCount);
WINBASEAPI PCHAR __cdecl MSVCRT$strstr(const char *haystack, const char *needle);
WINBASEAPI PCHAR __cdecl MSVCRT$strchr(const char *haystack, int needle);
WINBASEAPI int __cdecl MSVCRT$strncmp(const char *_Str1, const char *_Str2, size_t _MaxCount);
WINBASEAPI int __cdecl MSVCRT$_snprintf(char *__restrict__ _Dest, size_t _Count, const char *__restrict__ _Format, ...);
_CRTIMP uintptr_t __cdecl MSVCRT$_beginthreadex(void *_Security, unsigned _StackSize, _beginthreadex_proc_type _StartAddress, void *_ArgList, unsigned _InitFlag, unsigned *_ThrdAddr);
WINBASEAPI char *__cdecl MSVCRT$strcpy(char *__restrict__ __dst, const char *__restrict__ __src);
WINBASEAPI char *__cdecl MSVCRT$strcat(char *__restrict__ _Dest, const char *__restrict__ _Source);
WINBASEAPI int __cdecl MSVCRT$swprintf_s(wchar_t *buffer, size_t sizeOfBuffer, const wchar_t *format, ...);
WINBASEAPI void __cdecl MSVCRT$memset(void *dest, int c, size_t count);
WINBASEAPI int __cdecl MSVCRT$_vsnwprintf_s(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format, va_list argptr);
WINBASEAPI wchar_t *__cdecl MSVCRT$wcscat_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource);
WINBASEAPI errno_t __cdecl MSVCRT$wcscpy_s(wchar_t *_Dst, rsize_t _DstSize, const wchar_t *_Src);
WINBASEAPI void* __cdecl MSVCRT$malloc( size_t size);
WINBASEAPI void __cdecl MSVCRT$free( void* memblock);
WINBASEAPI size_t __cdecl MSVCRT$wcstombs(char* _Dest, const wchar_t* _Source, size_t _MaxCount);
WINBASEAPI int __cdecl MSVCRT$memcmp(const void *buffer1, const void *buffer2, size_t count);
WINBASEAPI char* __cdecl  MSVCRT$strncpy (char * __dst, const char * __src, size_t __n);
WINBASEAPI char* __cdecl  MSVCRT$strncat (char * _Dest,const char * _Source, size_t __n);
DECLSPEC_IMPORT int WINAPI MSVCRT$strcmp(const char*, const char*);
WINBASEAPI int WINAPI MSVCRT$sprintf(char * str, const char * format, ... );
DECLSPEC_IMPORT WINBASEAPI int __cdecl MSVCRT$printf(const char * __restrict__ _Format,...);
DECLSPEC_IMPORT WINBASEAPI size_t __cdecl MSVCRT$strlen(const char *_Str);
DECLSPEC_IMPORT WINBASEAPI void *__cdecl MSVCRT$memcpy(void * __restrict__ _Dst,const void * __restrict__ _Src,size_t _MaxCount);


// KERNEL32
WINBASEAPI LPWSTR WINAPI KERNEL32$lstrcpynW (LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength);
WINBASEAPI LPWSTR WINAPI KERNEL32$lstrcatW (LPWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI KERNEL32$WideCharToMultiByte (UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);
DECLSPEC_IMPORT DWORD WINAPI KERNEL32$CloseHandle(HANDLE hObjec);
DECLSPEC_IMPORT HANDLE WINAPI KERNEL32$CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,	LPSECURITY_ATTRIBUTES lpSecurityAttributes,	DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI WINBOOL WINAPI KERNEL32$SetEvent(HANDLE hEvent);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(VOID);
WINBASEAPI DWORD WINAPI KERNEL32$WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
WINBASEAPI WINBOOL WINAPI KERNEL32$TerminateThread(HANDLE hThread, DWORD dwExitCode);
WINBASEAPI HANDLE WINAPI KERNEL32$CreateEventA(LPSECURITY_ATTRIBUTES lpEventAttributes, WINBOOL bManualReset, WINBOOL bInitialState, LPCSTR lpName);
WINADVAPI WINAPI HMODULE KERNEL32$GetModuleHandleA(LPCSTR lpModuleName);
WINADVAPI WINAPI FARPROC KERNEL32$GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
WINADVAPI WINAPI HANDLE KERNEL32$CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID);
WINADVAPI WINAPI BOOL KERNEL32$Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
WINADVAPI WINAPI BOOL KERNEL32$Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
WINADVAPI WINAPI BOOL KERNEL32$Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
WINADVAPI WINAPI BOOL KERNEL32$Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
WINADVAPI WINAPI HANDLE KERNEL32$OpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);
WINADVAPI WINAPI SIZE_T KERNEL32$VirtualQueryEx(HANDLE hProcess,LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength);
WINADVAPI WINAPI BOOL KERNEL32$ReadProcessMemory(HANDLE hProcess,LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
WINADVAPI WINAPI BOOL KERNEL32$VirtualProtectEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
WINADVAPI WINAPI BOOL KERNEL32$WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
WINBASEAPI LPVOID WINAPI KERNEL32$HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI HANDLE WINAPI KERNEL32$GetProcessHeap();
WINBASEAPI BOOL WINAPI KERNEL32$HeapFree(HANDLE, DWORD, PVOID);
WINBASEAPI void WINAPI KERNEL32$OutputDebugStringW(LPCWSTR lpOutputString);
WINBASEAPI HMODULE WINAPI KERNEL32$LoadLibraryA(LPCSTR lpLibFileName);
WINBASEAPI BOOL WINAPI KERNEL32$FreeLibrary(HMODULE hLibModule);
WINBASEAPI BOOL WINAPI KERNEL32$LocalFree(HLOCAL hMem);
WINBASEAPI int WINAPI KERNEL32$MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
WINBASEAPI HANDLE WINAPI KERNEL32$CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI BOOL WINAPI KERNEL32$SetFileInformationByHandle(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize);
WINBASEAPI DWORD WINAPI KERNEL32$GetModuleFileNameW(HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
WINBASEAPI BOOL WINAPI KERNEL32$WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
WINBASEAPI DWORD   WINAPI KERNEL32$GetFileSize (HANDLE hFile, LPDWORD lpFileSizeHigh);
WINBASEAPI HGLOBAL WINAPI KERNEL32$GlobalAlloc (UINT uFlags, SIZE_T dwBytes);
WINBASEAPI HGLOBAL WINAPI KERNEL32$GlobalReAlloc (HGLOBAL hMem, SIZE_T dwBytes, UINT uFlags);
WINBASEAPI BOOL WINAPI    KERNEL32$ReadFile (HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
WINBASEAPI HGLOBAL WINAPI KERNEL32$GlobalFree (HGLOBAL hMem);
WINBASEAPI DWORD WINAPI KERNEL32$GetFileType(HANDLE hFile);
WINBASEAPI BOOL WINAPI    KERNEL32$DuplicateHandle (HANDLE hSourceProcessHandle, HANDLE hSourceHandle, HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle, DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwOptions);
WINBASEAPI DWORD WINAPI   KERNEL32$SetFilePointer (HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
DECLSPEC_IMPORT     WINBASEAPI HANDLE WINAPI KERNEL32$GetCurrentThread(VOID);
DECLSPEC_IMPORT     WINBASEAPI WINBOOL WINAPI KERNEL32$ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
DECLSPEC_IMPORT     WINBASEAPI DWORD WINAPI KERNEL32$GetTickCount(VOID);

// OLE32
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CLSIDFromString (LPCOLESTR lpsz, LPCLSID pclsid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$IIDFromString (LPCOLESTR lpsz, LPIID lpiid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoInitializeEx (LPVOID pvReserved, DWORD dwCoInit);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoCreateInstance (REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv);
DECLSPEC_IMPORT void	WINAPI OLE32$CoTaskMemFree(LPVOID pv);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CreateStreamOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease, LPSTREAM *ppstm);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoUninitialize (void);
DECLSPEC_IMPORT	HRESULT WINAPI OLE32$CoSetProxyBlanket(IUnknown* pProxy, DWORD dwAuthnSvc, DWORD dwAuthzSvc, OLECHAR* pServerPrincName, DWORD dwAuthnLevel, DWORD dwImpLevel, RPC_AUTH_IDENTITY_HANDLE pAuthInfo, DWORD dwCapabilities);


// BCRYPT
WINBASEAPI NTSTATUS WINAPI BCRYPT$BCryptOpenAlgorithmProvider(BCRYPT_ALG_HANDLE *phAlgorithm, LPCWSTR pszAlgId, LPCWSTR pszImplementation, ULONG dwFlags);
WINBASEAPI NTSTATUS WINAPI BCRYPT$BCryptCreateHash(BCRYPT_ALG_HANDLE hAlgorithm, BCRYPT_HASH_HANDLE *phHash, PUCHAR pbHashObject, ULONG cbHashObject, PUCHAR pbSecret, ULONG cbSecret, ULONG dwFlags);
WINBASEAPI NTSTATUS WINAPI BCRYPT$BCryptHashData(BCRYPT_HASH_HANDLE hHash, PUCHAR pbInput, ULONG cbInput, ULONG dwFlags);
WINBASEAPI NTSTATUS WINAPI BCRYPT$BCryptFinishHash(BCRYPT_HASH_HANDLE hHash, PUCHAR pbOutput, ULONG cbOutput, ULONG dwFlags);
WINBASEAPI NTSTATUS WINAPI BCRYPT$BCryptDestroyHash(BCRYPT_HASH_HANDLE hHash);
WINBASEAPI NTSTATUS WINAPI BCRYPT$BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE hAlgorithm, ULONG dwFlags);


// CRYPT32
WINIMPM WINBOOL WINAPI CRYPT32$CryptBinaryToStringA(CONST BYTE *pbBinary, DWORD cbBinary, DWORD dwFlags, LPSTR pszString, DWORD *pcchString);
WINBASEAPI BOOL WINAPI    CRYPT32$CryptStringToBinaryA (LPCSTR pszString, DWORD cchString, DWORD dwFlags, BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags);
WINBASEAPI BOOL  WINAPI   CRYPT32$CryptUnprotectData (DATA_BLOB *pDataIn, LPWSTR *ppszDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct, DWORD dwFlags, DATA_BLOB *pDataOut);


// ADVAPI32
WINBASEAPI WINBOOL WINAPI ADVAPI32$SystemFunction036(PVOID RandomBuffer, ULONG RandomBufferLength);
WINBASEAPI ULONG WINAPI ADVAPI32$EventRegister(LPCGUID ProviderId, PENABLECALLBACK EnableCallback, PVOID CallbackContext, PREGHANDLE RegHandle);
WINBASEAPI ULONG WINAPI ADVAPI32$EventWrite(REGHANDLE RegHandle, PCEVENT_DESCRIPTOR EventDescriptor, ULONG UserDataCount, PEVENT_DATA_DESCRIPTOR UserData);
WINBASEAPI ULONG WINAPI ADVAPI32$EventUnregister(REGHANDLE RegHandle);
WINADVAPI WINBOOL WINAPI ADVAPI32$RevertToSelf();
WINADVAPI WINBOOL WINAPI ADVAPI32$OpenProcessToken (HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
WINADVAPI WINBOOL WINAPI ADVAPI32$DuplicateTokenEx(HANDLE,DWORD,LPSECURITY_ATTRIBUTES,SECURITY_IMPERSONATION_LEVEL,TOKEN_TYPE,PHANDLE);
WINADVAPI WINBOOL WINAPI ADVAPI32$ImpersonateLoggedOnUser(HANDLE);
DECLSPEC_IMPORT     WINADVAPI WINBOOL WINAPI ADVAPI32$OpenThreadToken(HANDLE ThreadHandle, DWORD DesiredAccess, BOOL OpenAsSelf, PHANDLE TokenHandle);
DECLSPEC_IMPORT     WINADVAPI BOOL WINAPI ADVAPI32$GetTokenInformation(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength, PDWORD ReturnLength);


// USER32
WINUSERAPI int WINAPI USER32$GetWindowTextA(HWND hWnd, LPSTR lpString, int nMaxCount);
WINUSERAPI LRESULT WINAPI USER32$SendMessageTimeoutW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult);
WINUSERAPI int WINAPI USER32$EnumDesktopWindows(HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam);


// WS2_32
WINBASEAPI SOCKET WINAPI WS2_32$send(SOCKET s, const char *buf, int len, int flags);
WINBASEAPI int WINAPI WS2_32$closesocket(SOCKET s);
WINBASEAPI int WINAPI WS2_32$recv(SOCKET s, char *buf, int len, int flags);
WINBASEAPI u_short WINAPI WS2_32$htons(u_short hostshort);
WINBASEAPI int WINAPI WS2_32$bind(SOCKET s, const struct sockaddr *addr, int namelen);
WINBASEAPI int WINAPI WS2_32$socket(int af, int type, int protocol);
WINBASEAPI int WINAPI WS2_32$listen(SOCKET s, int backlog);
WINBASEAPI SOCKET WINAPI WS2_32$accept(SOCKET s, struct sockaddr *addr, int *addrlen);
WINBASEAPI int WINAPI WS2_32$WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
WINBASEAPI int WINAPI WS2_32$WSACleanup(void);


// WSOCK32
WINBASEAPI unsigned long WINAPI WSOCK32$inet_addr(const char *cp);


// SHELL32
WINBASEAPI HINSTANCE WINAPI SHELL32$ShellExecuteA(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd);
WINBASEAPI SHFOLDERAPI WINAPI SHELL32$SHGetFolderPathA(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPSTR pszPath);


// WINHTTP
WINBASEAPI HINTERNET WINAPI WINHTTP$WinHttpOpen(LPCWSTR, DWORD, LPCWSTR, LPCWSTR, DWORD);
WINBASEAPI HINTERNET WINAPI WINHTTP$WinHttpConnect(HINTERNET, LPCWSTR, INTERNET_PORT, DWORD);
WINBASEAPI HINTERNET WINAPI WINHTTP$WinHttpOpenRequest(HINTERNET, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR *, DWORD);
WINBASEAPI WINBOOL WINAPI WINHTTP$WinHttpAddRequestHeaders(HINTERNET, LPCWSTR, DWORD, DWORD);
WINBASEAPI WINBOOL WINAPI WINHTTP$WinHttpSendRequest(HINTERNET, LPCWSTR, DWORD, LPVOID, DWORD, DWORD, DWORD_PTR);
WINBASEAPI WINBOOL WINAPI WINHTTP$WinHttpReceiveResponse(HINTERNET, LPVOID);
WINBASEAPI WINBOOL WINAPI WINHTTP$WinHttpReadData(HINTERNET, LPVOID, DWORD, LPDWORD);
WINBASEAPI WINBOOL WINAPI WINHTTP$WinHttpCloseHandle(HINTERNET);


// RPCRT4
DECLSPEC_IMPORT RPC_STATUS WINAPI RPCRT4$RpcBindingFromStringBindingW(RPC_WSTR StringBinding, RPC_BINDING_HANDLE *Binding);
DECLSPEC_IMPORT RPC_STATUS WINAPI RPCRT4$RpcStringBindingComposeW(RPC_WSTR ObjUuid, RPC_WSTR ProtSeq, RPC_WSTR NetworkAddr, RPC_WSTR Endpoint, RPC_WSTR Options, RPC_WSTR *StringBinding);
DECLSPEC_IMPORT RPC_STATUS WINAPI RPCRT4$RpcBindingSetAuthInfoExW(RPC_BINDING_HANDLE Binding, RPC_WSTR ServerPrincName, unsigned long AuthnLevel, unsigned long AuthnSvc, RPC_AUTH_IDENTITY_HANDLE AuthIdentity, unsigned long AuthzSvc, RPC_SECURITY_QOS *SecurityQOS);
DECLSPEC_IMPORT RPC_STATUS WINAPI RPCRT4$RpcBindingFree(RPC_BINDING_HANDLE *Binding);
DECLSPEC_IMPORT RPC_STATUS WINAPI RPCRT4$RpcStringFreeW(RPC_WSTR *String);
DECLSPEC_IMPORT CLIENT_CALL_RETURN RPC_VAR_ENTRY RPCRT4$NdrClientCall2(PMIDL_STUB_DESC pStubDescriptor, PFORMAT_STRING  pFormat, ...);


// SHLWAPI
WINBASEAPI BOOL WINAPI SHLWAPI$PathFileExistsW(LPCWSTR pszPath);
WINBASEAPI LPSTR WINAPI SHLWAPI$StrStrIA(LPCSTR lpFirst,LPCSTR lpSrch);
WINBASEAPI BOOL WINAPI SHLWAPI$PathAppendA(LPSTR pszPath, LPCSTR pszMore);

// NTDLL
DECLSPEC_IMPORT NTSTATUS WINAPI NTDLL$NtQuerySystemInformation(int SystemInformationClass,PVOID SystemInformation,ULONG SystemInformationLength,PULONG ReturnLength);
DECLSPEC_IMPORT NTSTATUS NTAPI NTDLL$NtQueryObject(HANDLE, OBJECT_INFORMATION_CLASS, PVOID, ULONG, PULONG);


// OLEAUT32
WINBASEAPI BSTR WINAPI OLEAUT32$SysAllocStringByteLen(LPCSTR psz,UINT len);
WINBASEAPI void WINAPI OLEAUT32$SysFreeString(BSTR);
WINBASEAPI UINT WINAPI OLEAUT32$SysStringByteLen(BSTR bstr);


// NCRYPT
DECLSPEC_IMPORT SECURITY_STATUS WINAPI NCRYPT$NCryptFreeObject (NCRYPT_HANDLE hObject);
DECLSPEC_IMPORT SECURITY_STATUS WINAPI NCRYPT$NCryptDecrypt (NCRYPT_KEY_HANDLE hKey, PBYTE pbInput, DWORD cbInput, VOID *pPaddingInfo, PBYTE pbOutput, DWORD cbOutput, DWORD *pcbResult, DWORD dwFlags);
DECLSPEC_IMPORT SECURITY_STATUS WINAPI NCRYPT$NCryptOpenKey (NCRYPT_PROV_HANDLE hProvider, NCRYPT_KEY_HANDLE *phKey, LPCWSTR pszKeyName, DWORD dwLegacyKeySpec, DWORD dwFlags);
DECLSPEC_IMPORT SECURITY_STATUS WINAPI NCRYPT$NCryptOpenStorageProvider (NCRYPT_PROV_HANDLE *phProvider, LPCWSTR pszProviderName, DWORD dwFlags);

// SECUR32
DECLSPEC_IMPORT     WINBASEAPI DWORD WINAPI SECUR32$AcquireCredentialsHandleA(LPSTR, LPSTR, unsigned long, void*, void*, SEC_GET_KEY_FN, void *, PCredHandle, PTimeStamp);
DECLSPEC_IMPORT     WINBASEAPI DWORD WINAPI SECUR32$InitializeSecurityContextA(PCredHandle, PCtxtHandle, SEC_CHAR*, unsigned long, unsigned long, unsigned long, PSecBufferDesc, unsigned long, PCtxtHandle, PSecBufferDesc, unsigned long *, PTimeStamp);
DECLSPEC_IMPORT     WINBASEAPI DWORD WINAPI SECUR32$AcceptSecurityContext(PCredHandle, PCtxtHandle, PSecBufferDesc, unsigned long, unsigned long, PCtxtHandle, PSecBufferDesc, unsigned long *, PTimeStamp);
DECLSPEC_IMPORT     KSECDDDECLSPEC SECURITY_STATUS SEC_ENTRY SECUR32$QuerySecurityContextToken(PCtxtHandle phContext, void **Token);
DECLSPEC_IMPORT     WINBASEAPI SECURITY_STATUS WINAPI SECUR32$FreeCredentialsHandle(PCredHandle phCredential);
DECLSPEC_IMPORT     WINBASEAPI SECURITY_STATUS WINAPI SECUR32$DeleteSecurityContext(PCtxtHandle phContext);

#endif // end DEFINTIIONS_H