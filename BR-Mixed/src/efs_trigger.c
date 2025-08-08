#include <windows.h>
#include "badger_exports.h"

DECLSPEC_IMPORT DWORD WINAPI Kernel32$CloseHandle(HANDLE hObjec);
DECLSPEC_IMPORT HANDLE WINAPI Kernel32$CreateFileA(
	LPCSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
);

void coffee( char ** argv, int argc, WCHAR** dispatch) {
	LPSTR pszFilePath = ".\\test.txt";

	if(argc >= 1) {
		pszFilePath = argv[0];
	}

	BadgerDispatch(dispatch, "[*] Creating file: '%s'\n", pszFilePath);
	HANDLE file = Kernel32$CreateFileA(pszFilePath, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_ATTRIBUTE_ENCRYPTED|FILE_FLAG_DELETE_ON_CLOSE, NULL);

	if (!file || file == INVALID_HANDLE_VALUE) {
		BadgerDispatch(dispatch, "[-] Error calling CreateFileA: %d\n", GetLastError());
	}

	BadgerDispatch(dispatch, "[*] Successfully created file. EFS service should be started.\n");
	if(file) Kernel32$CloseHandle(file);
}
