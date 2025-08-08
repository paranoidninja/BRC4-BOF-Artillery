#include <lm.h>
#include <dsgetdc.h>

__declspec(dllimport) __stdcall DWORD  NetApi32$DsGetDcNameA(LPCSTR ComputerName, LPCSTR DomainName, GUID*DomainGuid, LPCSTR SiteName, ULONG Flags, PDOMAIN_CONTROLLER_INFOA *DomainControllerInfo);
__declspec(dllimport) __stdcall DWORD  Netapi32$NetShareEnum(LPWSTR servername, DWORD level, LPBYTE  *bufptr, DWORD prefmaxlen, LPDWORD entriesread, LPDWORD totalentries, LPDWORD resume_handle);
__declspec(dllimport) __stdcall DWORD  Netapi32$NetApiBufferFree(LPVOID Buffer);
