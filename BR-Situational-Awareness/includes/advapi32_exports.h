#pragma once
#include "common.h"

#ifndef __ADVAPI_H__
#define __ADVAPI_H__

#define AdjustTokenPrivileges       Advapi32$AdjustTokenPrivileges
#define CloseServiceHandle          Advapi32$CloseServiceHandle
#define CredBackupCredentials       Advapi32$CredBackupCredentials
#define CreateProcessAsUserW        Advapi32$CreateProcessAsUserW
#define CryptAcquireContextA        Advapi32$CryptAcquireContextA
#define CryptAcquireContextW        Advapi32$CryptAcquireContextW
#define CryptCreateHash             Advapi32$CryptCreateHash
#define CryptHashData               Advapi32$CryptHashData
#define CryptDestroyHash            Advapi32$CryptDestroyHash
#define CryptGetHashParam           Advapi32$CryptGetHashParam
#define CryptReleaseContext         Advapi32$CryptReleaseContext

#define DuplicateTokenEx Advapi32$DuplicateTokenEx

#define EnumServicesStatusExW Advapi32$EnumServicesStatusExW
#define EventRegister Advapi32$EventRegister
#define EventUnregister Advapi32$EventUnregister
#define EventWrite Advapi32$EventWrite

#define GetSidSubAuthority Advapi32$GetSidSubAuthority
#define GetSidSubAuthorityCount Advapi32$GetSidSubAuthorityCount
#define GetTokenInformation Advapi32$GetTokenInformation
#define LookupPrivilegeValueA Advapi32$LookupPrivilegeValueA
#define LsaOpenPolicy Advapi32$LsaOpenPolicy
#define LsaQueryInformationPolicy Advapi32$LsaQueryInformationPolicy
#define ImpersonateLoggedOnUser Advapi32$ImpersonateLoggedOnUser
#define OpenProcessToken Advapi32$OpenProcessToken
#define OpenThreadToken Advapi32$OpenThreadToken
#define OpenSCManagerA Advapi32$OpenSCManagerA
#define OpenServiceA Advapi32$OpenServiceA
#define PrivilegeCheck Advapi32$PrivilegeCheck
#define QueryServiceStatusEx Advapi32$QueryServiceStatusEx
#define RevertToSelf Advapi32$RevertToSelf

#define RegCloseKey         Advapi32$RegCloseKey
#define RegConnectRegistryA Advapi32$RegConnectRegistryA
#define RegOpenKeyExA       Advapi32$RegOpenKeyExA
#define RegOpenKeyExW       Advapi32$RegOpenKeyExW
#define RegEnumKeyExA       Advapi32$RegEnumKeyExA
#define RegQueryValueExA    Advapi32$RegQueryValueExA
#define RegQueryValueExW    Advapi32$RegQueryValueExW

#define SetTokenInformation Advapi32$SetTokenInformation
#define SystemFunction032 Advapi32$SystemFunction032
#define I_QueryTagInformation Advapi32$I_QueryTagInformation

typedef enum _SC_SERVICE_TAG_QUERY_TYPE
{
	ServiceNameFromTagInformation = 1,
	ServiceNameReferencingModuleInformation,
	ServiceNameTagMappingInformation,
} SC_SERVICE_TAG_QUERY_TYPE, *PSC_SERVICE_TAG_QUERY_TYPE;


typedef struct _SC_SERVICE_TAG_QUERY
{
  ULONG   processId;
  ULONG   serviceTag;
  ULONG   reserved;
  PVOID   pBuffer;
} SC_SERVICE_TAG_QUERY, *PSC_SERVICE_TAG_QUERY;

typedef struct _PVOID_STRING {
  DWORD Length;
  DWORD MaximumLength;
  PVOID Buffer;
} PVOID_STRING, *PPVOID_STRING;


// Advapi32 Function headers
WINADVAPI WINAPI BOOL      Advapi32$AdjustTokenPrivileges(HANDLE TokenHandle, BOOL DisableAllPrivileges, PTOKEN_PRIVILEGES NewState, DWORD BufferLength, PTOKEN_PRIVILEGES PreviousState, PDWORD ReturnLength);

WINADVAPI WINAPI BOOL      Advapi32$CloseServiceHandle(SC_HANDLE hSCObject);
WINADVAPI WINAPI BOOL      Advapi32$CredBackupCredentials(HANDLE Token, LPCWSTR Path, PVOID Password, DWORD PasswordSize, DWORD Flags);
WINADVAPI WINAPI BOOL      Advapi32$CreateProcessAsUserW(HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID  lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
WINADVAPI WINAPI BOOL      Advapi32$CryptAcquireContextA(HCRYPTPROV *phProv, LPCSTR szContainer, LPCSTR szProvider, DWORD dwProvType, DWORD dwFlags);
WINADVAPI WINAPI BOOL      Advapi32$CryptAcquireContextW(HCRYPTPROV *phProv, LPCWSTR szContainer, LPCWSTR szProvider, DWORD dwProvType, DWORD dwFlags);
WINADVAPI WINAPI BOOL      Advapi32$CryptCreateHash(HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH *phHash);
WINADVAPI WINAPI BOOL      Advapi32$CryptHashData(HCRYPTHASH hHash, const BYTE *pbData, DWORD dwDataLen, DWORD dwFlags);
WINADVAPI WINAPI BOOL      Advapi32$CryptDestroyHash(HCRYPTHASH hHash);
WINADVAPI WINAPI BOOL      Advapi32$CryptGetHashParam(HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData, DWORD *pdwDataLen, DWORD dwFlags);
WINADVAPI WINAPI BOOL      Advapi32$CryptReleaseContext(HCRYPTPROV hProv, DWORD dwFlags);

WINADVAPI WINAPI BOOL      Advapi32$DuplicateTokenEx(HANDLE hExistingToken, DWORD dwDesiredAccess, LPSECURITY_ATTRIBUTES lpTokenAttributes, SECURITY_IMPERSONATION_LEVEL ImpersonationLevel, TOKEN_TYPE TokenType, PHANDLE phNewToken);

WINADVAPI WINAPI BOOL      Advapi32$EnumServicesStatusExW(SC_HANDLE hSCManager, SC_ENUM_TYPE InfoLevel, DWORD dwServiceType, DWORD dwServiceState, LPBYTE lpServices, DWORD cbBufSize, LPDWORD pcbBytesNeeded, LPDWORD lpServicesReturned, LPDWORD lpResumeHandle, LPCWSTR pszGroupName);
WINADVAPI WINAPI ULONG     Advapi32$EventRegister(LPCGUID ProviderId, PENABLECALLBACK EnableCallback, PVOID CallbackContext, PREGHANDLE RegHandle);
WINADVAPI WINAPI ULONG     Advapi32$EventUnregister(REGHANDLE RegHandle);
WINADVAPI WINAPI ULONG     Advapi32$EventWrite(REGHANDLE RegHandle, PEVENT_DESCRIPTOR EventDescriptor, ULONG UserDataCount, PEVENT_DATA_DESCRIPTOR UserData);

WINADVAPI WINAPI PDWORD    Advapi32$GetSidSubAuthority(_In_ PSID  pSid, _In_ DWORD nSubAuthority);
WINADVAPI WINAPI PUCHAR    Advapi32$GetSidSubAuthorityCount(_In_ PSID pSid);
WINADVAPI WINAPI BOOL      Advapi32$GetTokenInformation(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength, PDWORD ReturnLength);

WINADVAPI WINAPI BOOL      Advapi32$LookupPrivilegeValueA(LPCSTR, LPCSTR, PLUID);
WINADVAPI WINAPI NTSTATUS  Advapi32$LsaOpenPolicy(PLSA_UNICODE_STRING SystemName, PLSA_OBJECT_ATTRIBUTES ObjectAttributes, ACCESS_MASK DesiredAccess, PLSA_HANDLE PolicyHandle);
WINADVAPI WINAPI NTSTATUS  Advapi32$LsaQueryInformationPolicy(LSA_HANDLE PolicyHandle, POLICY_INFORMATION_CLASS InformationClass, PVOID *Buffer);

WINADVAPI WINAPI BOOL      Advapi32$ImpersonateLoggedOnUser(HANDLE hToken);

WINADVAPI WINAPI BOOL      Advapi32$OpenProcessToken(HANDLE, DWORD, PHANDLE);
WINADVAPI WINAPI BOOL      Advapi32$OpenThreadToken(HANDLE ThreadHandle, DWORD DesiredAccess, BOOL OpenAsSelf, PHANDLE TokenHandle);
WINADVAPI WINAPI SC_HANDLE Advapi32$OpenSCManagerA(_In_ LPCSTR lpMachineName, _In_ LPCSTR lpDatabaseName, _In_ DWORD dwDesiredAccess);
WINADVAPI WINAPI SC_HANDLE Advapi32$OpenServiceA(_In_ SC_HANDLE hSCManager, _In_ LPCSTR lpServiceName,_In_ DWORD dwDesiredAccess);

WINADVAPI WINAPI BOOL      Advapi32$PrivilegeCheck(_In_ HANDLE ClientToken, _Inout_ PPRIVILEGE_SET RequiredPrivileges, _Out_ LPBOOL pfResult);

WINADVAPI WINAPI BOOL      Advapi32$QueryServiceStatusEx(_In_ SC_HANDLE hService, _In_ SC_STATUS_TYPE InfoLevel, _Out_ LPBYTE lpBuffer, _In_ DWORD cbBufSize, _Out_ LPDWORD pcbBytesNeeded);

WINADVAPI WINAPI BOOL      Advapi32$RevertToSelf();
WINADVAPI WINAPI LSTATUS   Advapi32$RegCloseKey(HKEY hKey);
WINADVAPI WINAPI LSTATUS   Advapi32$RegConnectRegistryA(LPCSTR lpMachineName, HKEY hKey, PHKEY phkResult);
WINADVAPI WINAPI LSTATUS   Advapi32$RegEnumKeyExA(HKEY hKey, DWORD dwIndex, LPSTR lpName, LPDWORD lpcchName, LPDWORD lpReserved, LPSTR lpClass, LPDWORD lpcchClass, PFILETIME lpftLastWriteTime);
WINADVAPI WINAPI LSTATUS   Advapi32$RegQueryValueExA(HKEY    hKey, LPCSTR  lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE  lpData, LPDWORD lpcbData);

WINADVAPI WINAPI LSTATUS   Advapi32$RegOpenKeyExA(HKEY   hKey, LPCSTR lpSubKey, DWORD  ulOptions, REGSAM samDesired, PHKEY  phkResult);
WINADVAPI WINAPI LSTATUS   Advapi32$RegOpenKeyExW(HKEY   hKey, LPCWSTR lpSubKey, DWORD  ulOptions, REGSAM samDesired, PHKEY  phkResult);
WINADVAPI WINAPI LSTATUS   Advapi32$RegQueryValueExW(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);


WINADVAPI WINAPI BOOL      Advapi32$SetTokenInformation(HANDLE TokenHandle, TOKEN_INFORMATION_CLASS TokenInformationClass, LPVOID TokenInformation, DWORD TokenInformationLength);
WINADVAPI WINAPI NTSTATUS  Advapi32$SystemFunction032(PPVOID_STRING source, PPVOID_STRING key);
WINADVAPI WINAPI ULONG     Advapi32$I_QueryTagInformation(PVOID, SC_SERVICE_TAG_QUERY_TYPE, PSC_SERVICE_TAG_QUERY);

#endif
