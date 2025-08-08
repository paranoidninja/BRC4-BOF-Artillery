#include "common.h"

void usage() {
    PRINT("[+] Usage:\n");
    PRINT("      findLoadedModule [modulepart] [opt:procnamepart]\n\n");
    PRINT("[+] Description:\n");
    PRINT("      Find what processes *modulepart* are loaded into, optionally searching just *procnamepart*");
}

BOOL ListModules(DWORD PID, const char * modSearchString)
{
	MODULEENTRY32 modinfo = {0};
	modinfo.dwSize = sizeof(MODULEENTRY32);
	HANDLE hSnap = INVALID_HANDLE_VALUE;
	BOOL retVal = FALSE;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
	BOOL more = Module32First(hSnap, &modinfo);
	while(more)
	{
		if(StrStrIA(modinfo.szExePath, modSearchString))
		{
			//May be beneficial to print off all hits even within a single process
			PRINT("%s\n", modinfo.szExePath);
			retVal = TRUE;
			//break;
		}
		more = Module32Next(hSnap, &modinfo);
	}

	if (hSnap != INVALID_HANDLE_VALUE) CloseHandle(hSnap);
	return retVal;
}

void ListProcesses(const char * procSearchString, const char * modSearchString) {
    //Get snapshop of all procs
	PROCESSENTRY32 procinfo = {0};
	procinfo.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnap = INVALID_HANDLE_VALUE;
	DWORD count = 0;
	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnap == INVALID_HANDLE_VALUE)
	{
		ERR_PRINT("CreateToolhelp32Snapshot");
		goto end;
	}

	//And now we Enumerate procs and Call up to List Modules with them
	BOOL more = Process32First(hSnap, &procinfo);
	//internal_printf("First call returned : %d\n", more);
	while(more)
	{
		if(!procSearchString || StrStrIA(procinfo.szExeFile, procSearchString))
		{
			if(ListModules(procinfo.th32ProcessID, modSearchString))
			{
				PRINT("%-10lu : %s\n", procinfo.th32ProcessID, procinfo.szExeFile);
				count++;
			}
		}
		more = Process32Next(hSnap, &procinfo);
	}
	//Check that we exited because we were done and not an error
	DWORD exitStatus = GetLastError();
	if(exitStatus != ERROR_NO_MORE_FILES)
	{
		EPRINT("[-] Unable to enumerate all processes: %lu", exitStatus);
		goto end;
	}

	if(!count)
	{
		PRINT("[+] Successfully enumerated all processes, but didn't find the requested module\n");
	}

	end:
	    if(hSnap != INVALID_HANDLE_VALUE) CloseHandle(hSnap); 

	return;
}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;

    // Check for help flag
    if (argc == 1) {
      if (
            (BadgerStrcmp(argv[0], "-h") == 0) ||
            (BadgerStrcmp(argv[0], "--help") == 0) ||
            (BadgerStrcmp(argv[0], "/?") == 0)
        ) {
        usage();
        return;
        }
    }

    if (argc > 2 || argc == 0) {
        usage();
        return;
    }

    char * modSearchString = NULL;
    char * procSearchString = NULL;

    if (argc >= 1) modSearchString = argv[0];
    if (argc == 2) procSearchString = argv[1];
 
    ListProcesses(procSearchString, modSearchString);   
}