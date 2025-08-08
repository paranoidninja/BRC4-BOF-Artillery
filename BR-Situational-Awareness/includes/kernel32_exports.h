#pragma once
#include "common.h"

#define intAlloc(size) Kernel32$HeapAlloc(Kernel32$GetProcessHeap(), HEAP_ZERO_MEMORY, size)
#define intFree(addr)  Kernel32$HeapFree(Kernel32$GetProcessHeap(), 0, addr)

// Kernel32 Function headers
#define CloseHandle Kernel32$CloseHandle
#define CreateFileA Kernel32$CreateFileA
#define CreateFileW Kernel32$CreateFileW
#define CreateMutexA Kernel32$CreateMutexA
#define CreateThread Kernel32$CreateThread
#define CreateToolhelp32Snapshot Kernel32$CreateToolhelp32Snapshot

#define DeleteCriticalSection               Kernel32$DeleteCriticalSection
#define DeleteFileA                         Kernel32$DeleteFileA
#define DeleteFileW                         Kernel32$DeleteFileW

#define EnterCriticalSection                Kernel32$EnterCriticalSection

#define FileTimeToSystemTime                Kernel32$FileTimeToSystemTime
#define FindClose                           Kernel32$FindClose
#define FindFirstFileA                      Kernel32$FindFirstFileA
#define FindFirstFileW                      Kernel32$FindFirstFileW
#define FindNextFileA                       Kernel32$FindNextFileA
#define FreeLibrary                         Kernel32$FreeLibrary

#define GetCurrentProcessId                 Kernel32$GetCurrentProcessId
#define GetDateFormatEx                     Kernel32$GetDateFormatEx

#define GetDiskFreeSpaceExA                 Kernel32$GetDiskFreeSpaceExA
#define GetFileAttributesW                  Kernel32$GetFileAttributesW
#define GetLocaleInfoEx                     Kernel32$GetLocaleInfoEx
#define GetFileSize                         Kernel32$GetFileSize
#define GetFileSizeEx                       Kernel32$GetFileSizeEx
#define GetLastError                        Kernel32$GetLastError
#define GetModuleHandleA                    Kernel32$GetModuleHandleA
#define GetProcAddress                      Kernel32$GetProcAddress
#define GetProcessId                        Kernel32$GetProcessId
#define GetProcessHeap                      Kernel32$GetProcessHeap
#define GlobalAlloc                         Kernel32$GlobalAlloc
#define GlobalFree                          Kernel32$GlobalFree
#define GetSystemInfo                       Kernel32$GetSystemInfo
#define GetSystemDefaultLocaleName          Kernel32$GetSystemDefaultLocaleName
#define GlobalMemoryStatusEx                Kernel32$GlobalMemoryStatusEx

#define InitializeCriticalSection           Kernel32$InitializeCriticalSection
#define IsWow64Process                      Kernel32$IsWow64Process

#define LeaveCriticalSection                Kernel32$LeaveCriticalSection
#define LoadLibraryA                        Kernel32$LoadLibraryA
#define LocalAlloc                          Kernel32$LocalAlloc
#define LocalFree                           Kernel32$LocalFree
#define LocaleNameToLCID                    Kernel32$LocaleNameToLCID

#define Module32First                       Kernel32$Module32First
#define Module32Next                        Kernel32$Module32Next

#define MultiByteToWideChar Kernel32$MultiByteToWideChar
#define QueryDosDeviceW Kernel32$QueryDosDeviceW
#define OpenProcess Kernel32$OpenProcess
#define OpenThread Kernel32$OpenThread
#define Process32First Kernel32$Process32First
#define Process32FirstW Kernel32$Process32FirstW
#define Process32Next Kernel32$Process32Next
#define Process32NextW Kernel32$Process32NextW
#define ProcessIdToSessionId Kernel32$ProcessIdToSessionId
#define QueryFullProcessImageNameA Kernel32$QueryFullProcessImageNameA
#define QueryFullProcessImageNameW Kernel32$QueryFullProcessImageNameW
#define ReadFile Kernel32$ReadFile
#define ReleaseMutex Kernel32$ReleaseMutex
#define ResumeThread Kernel32$ResumeThread
#define ReadProcessMemory Kernel32$ReadProcessMemory
#define SetLastError Kernel32$SetLastError
#define Sleep Kernel32$Sleep
#define SuspendThread                           Kernel32$SuspendThread
#define SystemTimeToTzSpecificLocalTime         Kernel32$SystemTimeToTzSpecificLocalTime
#define TerminateThread                         Kernel32$TerminateThread
#define Thread32First Kernel32$Thread32First
#define Thread32Next Kernel32$Thread32Next
#define VirtualQueryEx Kernel32$VirtualQueryEx
#define WaitForMultipleObjects Kernel32$WaitForMultipleObjects
#define WaitForSingleObject Kernel32$WaitForSingleObject
#define WriteFile Kernel32$WriteFile
#define WideCharToMultiByte Kernel32$WideCharToMultiByte

WINADVAPI WINAPI BOOL     Kernel32$CloseHandle(_In_ HANDLE hObject);
WINADVAPI WINAPI HANDLE   Kernel32$CreateFileA(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
WINADVAPI WINAPI HANDLE   Kernel32$CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINADVAPI WINAPI HANDLE   Kernel32$CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);
WINADVAPI WINAPI HANDLE   Kernel32$CreateThread(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE,__drv_aliasesMem LPVOID, DWORD, LPDWORD);
WINADVAPI WINAPI HANDLE   Kernel32$CreateToolhelp32Snapshot(_In_ DWORD dwFlags, _In_ DWORD th32ProcessID);

WINADVAPI WINAPI VOID     Kernel32$DeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINADVAPI WINAPI BOOL     Kernel32$DeleteFileA(LPCSTR);
WINADVAPI WINAPI BOOL     Kernel32$DeleteFileW(LPCWSTR lpFileName);

WINADVAPI WINAPI VOID     Kernel32$EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);

WINADVAPI WINAPI BOOL     Kernel32$FileTimeToSystemTime(const FILETIME *lpFileTime, LPSYSTEMTIME lpSystemTime);
WINADVAPI WINAPI BOOL     Kernel32$FindClose(HANDLE);
WINADVAPI WINAPI HANDLE   Kernel32$FindFirstFileA(LPCSTR, LPWIN32_FIND_DATAA);
WINADVAPI WINAPI HANDLE   Kernel32$FindFirstFileW(LPCWSTR, LPWIN32_FIND_DATAA);
WINADVAPI WINAPI BOOL     Kernel32$FindNextFileA(HANDLE, LPWIN32_FIND_DATAA);
WINADVAPI WINAPI BOOL     Kernel32$FreeLibrary(_In_ HMODULE hLibModule);

WINADVAPI WINAPI DWORD    Kernel32$GetCurrentProcessId();
WINADVAPI WINAPI int      Kernel32$GetDateFormatEx(LPCWSTR lpLocaleName, DWORD dwFlags, const SYSTEMTIME *lpDate,LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate, LPCWSTR lpCalendar);

WINADVAPI WINAPI BOOL     Kernel32$GetDiskFreeSpaceExA(LPCSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes);
WINADVAPI WINAPI int      Kernel32$GetLocaleInfoEx(LPCWSTR lpLocaleName, LCTYPE LCType, LPWSTR lpLCData, int cchData);
WINADVAPI WINAPI HANDLE   Kernel32$GetProcessHeap();
WINADVAPI WINAPI DWORD    Kernel32$GetFileAttributesW(LPCWSTR lpFileName);
WINADVAPI WINAPI DWORD    Kernel32$GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);\
WINADVAPI WINAPI BOOL     Kernel32$GetFileSizeEx(HANDLE, PLARGE_INTEGER);
WINADVAPI WINAPI DWORD    Kernel32$GetLastError();
WINADVAPI WINAPI HMODULE  Kernel32$GetModuleHandleA(_In_ LPCSTR lpModuleName);
WINADVAPI WINAPI FARPROC  Kernel32$GetProcAddress(_In_ HMODULE hModule, _In_ LPCSTR lpProcName);
WINADVAPI WINAPI DWORD    Kernel32$GetProcessId(HANDLE Process);
WINADVAPI WINAPI HGLOBAL  Kernel32$GlobalAlloc(UINT uFlags, SIZE_T dwBytes);
WINADVAPI WINAPI HGLOBAL  Kernel32$GlobalFree(HGLOBAL hMem);
WINADVAPI WINAPI BOOL     Kernel32$GlobalMemoryStatusEx(LPMEMORYSTATUSEX lpBuffer);
WINADVAPI WINAPI VOID     Kernel32$GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
WINADVAPI WINAPI int      Kernel32$GetSystemDefaultLocaleName(LPWSTR lpLocaleName, int cchLocaleName);

WINADVAPI WINAPI LPVOID   Kernel32$HeapAlloc(HANDLE hHeap, DWORD  dwFlags, SIZE_T dwBytes);
WINADVAPI WINAPI BOOL     Kernel32$HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);


WINADVAPI WINAPI VOID     Kernel32$InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINADVAPI WINAPI BOOL     Kernel32$IsWow64Process(_In_ HANDLE hProcess, _Out_ PBOOL Wow64Process);

WINADVAPI WINAPI VOID     Kernel32$LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
WINADVAPI WINAPI HMODULE  Kernel32$LoadLibraryA(_In_ LPCSTR lpLibFileName);
WINADVAPI WINAPI LCID     Kernel32$LocaleNameToLCID(LPCWSTR lpName, DWORD dwFlags);
WINADVAPI WINAPI HLOCAL   Kernel32$LocalAlloc(_In_ UINT   uFlags, _In_ SIZE_T uBytes);
WINADVAPI WINAPI HLOCAL   Kernel32$LocalFree(_In_ HLOCAL hMem);

WINADVAPI WINAPI int      Kernel32$MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);
WINADVAPI WINAPI BOOL     Kernel32$Module32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
WINADVAPI WINAPI BOOL     Kernel32$Module32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme);

WINADVAPI WINAPI DWORD    Kernel32$QueryDosDeviceW(_In_opt_ LPCWSTR lpDeviceName, _Out_ LPWSTR  lpTargetPath, _In_ DWORD ucchMax);

WINADVAPI WINAPI HANDLE   Kernel32$OpenProcess(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId);
WINADVAPI WINAPI HANDLE   Kernel32$OpenThread(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwThreadId);

WINADVAPI WINAPI BOOL     Kernel32$Process32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
WINADVAPI WINAPI BOOL     Kernel32$Process32FirstW(HANDLE hSnapshot, LPPROCESSENTRY32W lppe);
WINADVAPI WINAPI BOOL     Kernel32$Process32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
WINADVAPI WINAPI BOOL     Kernel32$Process32NextW(HANDLE hSnapshot, LPPROCESSENTRY32W lppe);
WINADVAPI WINAPI BOOL     Kernel32$ProcessIdToSessionId(DWORD dwProcessId, DWORD *pSessionId);

WINADVAPI WINAPI BOOL     Kernel32$QueryFullProcessImageNameA(HANDLE hProcess, DWORD  dwFlags, LPSTR lpExeName, PDWORD lpdwSize);
WINADVAPI WINAPI BOOL     Kernel32$QueryFullProcessImageNameW(HANDLE hProcess, DWORD  dwFlags, LPWSTR lpExeName, PDWORD lpdwSize);

WINADVAPI WINAPI BOOL     Kernel32$ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
WINADVAPI WINAPI BOOL     Kernel32$ReleaseMutex(HANDLE hMutex);
WINADVAPI WINAPI DWORD    Kernel32$ResumeThread(_In_ HANDLE hThread);
WINADVAPI WINAPI BOOL     Kernel32$ReadProcessMemory(_In_ HANDLE hProcess, _In_ LPCVOID lpBaseAddress, _Out_ LPVOID lpBuffer, _In_ SIZE_T nSize, _Out_ SIZE_T *lpNumberOfBytesRead);

WINADVAPI WINAPI void     Kernel32$SetLastError(DWORD dwErrCode);
WINADVAPI WINAPI void     Kernel32$Sleep(DWORD dwMilliseconds);
WINADVAPI WINAPI DWORD    Kernel32$SuspendThread(_In_ HANDLE hThread);
WINADVAPI WINAPI BOOL     Kernel32$SystemTimeToTzSpecificLocalTime(const TIME_ZONE_INFORMATION *lpTimeZoneInformation, const SYSTEMTIME *lpUniversalTime, LPSYSTEMTIME lpLocalTime
);

WINADVAPI WINAPI DWORD    Kernel32$TerminateThread(_Inout_ HANDLE hThread, _Out_ DWORD dwExitCode);
WINADVAPI WINAPI BOOL     Kernel32$Thread32First(_In_ HANDLE hSnapshot, _Inout_ LPTHREADENTRY32 lpte);
WINADVAPI WINAPI BOOL     Kernel32$Thread32Next(_In_ HANDLE hSnapshot, _Out_ LPTHREADENTRY32 lpte);

WINADVAPI WINAPI SIZE_T   Kernel32$VirtualQueryEx(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

WINADVAPI WINAPI DWORD    Kernel32$WaitForMultipleObjects(DWORD, const HANDLE*, BOOL, DWORD);
WINADVAPI WINAPI DWORD    Kernel32$WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
WINADVAPI WINAPI BOOL     Kernel32$WriteFile(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
WINADVAPI WINAPI int      Kernel32$WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);
WINADVAPI WINAPI DWORD    Kernel32$WTSGetActiveConsoleSessionId();

