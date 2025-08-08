#include "common.h"

#define DIV 1048576

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;

    // Get dat memory
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);

    if (GlobalMemoryStatusEx(&statex) == 0) {
		ERR_PRINT("GlobalMemoryStatusEx");
		return;
	}

    PRINT("[+] Memory Used:\t%I64dMB/%I64dMB\n", 
        (statex.ullTotalPhys - statex.ullAvailPhys) / DIV,
		statex.ullTotalPhys / DIV);

    // And now the primary disk
	ULARGE_INTEGER totalBytes;
	ULARGE_INTEGER freeBytes;


    if (GetDiskFreeSpaceExA(NULL, NULL, &totalBytes, &freeBytes) == 0) {
        ERR_PRINT("GetDiskFreeSpaceExA");
        return;
    }

    PRINT("[+] Free Space:\t%lu MB\n", freeBytes.QuadPart / DIV);
    PRINT("[+] Total Space:\t%lu MB\n", totalBytes.QuadPart / DIV);
	
}