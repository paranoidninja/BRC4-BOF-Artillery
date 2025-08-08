#pragma once 
#include "common.h"

#ifndef LIST_MODULES_ALL
    #define LIST_MODULES_ALL 0x03
#endif

#define EnumProcessModulesEx            Psapi$EnumProcessModulesEx
#define GetModuleBaseNameW              Psapi$GetModuleBaseNameW
#define GetModuleFileNameExW            Psapi$GetModuleFileNameExW
#define GetModuleInformation            Psapi$GetModuleInformation

typedef struct _MODULEINFO {
    LPVOID lpBaseOfDll;
    DWORD  SizeOfImage;
    LPVOID EntryPoint;
} MODULEINFO, *LPMODULEINFO;

WINADVAPI WINAPI BOOL     Psapi$EnumProcessModulesEx(HANDLE  hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded, DWORD dwFilterFlag);
WINADVAPI WINAPI DWORD    Psapi$GetModuleFileNameExW(HANDLE  hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
WINADVAPI WINAPI DWORD    Psapi$GetModuleBaseNameW(HANDLE  hProcess, HMODULE hModule, LPWSTR  lpBaseName, DWORD   nSize);
WINADVAPI WINAPI BOOL     Psapi$GetModuleInformation(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb);