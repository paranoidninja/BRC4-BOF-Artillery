#include <windows.h>

#include "definitions.h"
#include "badger_exports.h"


void coffee( char ** argv, int argc, WCHAR** dispatch) {
	LPSTR pszFilePath = ".\\test.txt";

	if(argc >= 1) {
		pszFilePath = argv[0];
	}

	BadgerDispatch(dispatch, "[*] Creating file: '%s'\n", pszFilePath);
	HANDLE file = KERNEL32$CreateFileA(pszFilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_ENCRYPTED|FILE_FLAG_DELETE_ON_CLOSE, NULL);

	if (!file || file == INVALID_HANDLE_VALUE) {
		BadgerDispatch(dispatch, "[-] Error calling CreateFileA: %d\n", KERNEL32$GetLastError());
		return;
	}

	BadgerDispatch(dispatch, "[+] Successfully created file. EFS service should be started.\n");
	if(file) KERNEL32$CloseHandle(file);
}
