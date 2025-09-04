#include <windows.h>
#include <stdlib.h>
#include "../badger_exports.h"


DECLSPEC_IMPORT LSTATUS WINAPI Advapi32$RegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
DECLSPEC_IMPORT LSTATUS WINAPI Advapi32$RegConnectRegistryA(LPCSTR lpMachineName, HKEY hKey, PHKEY phkResu);
DECLSPEC_IMPORT LSTATUS WINAPI Advapi32$RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, const LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
DECLSPEC_IMPORT LSTATUS WINAPI Advapi32$RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE *lpData, DWORD cbData);
DECLSPEC_IMPORT LSTATUS WINAPI Advapi32$RegCloseKey(HKEY hKey);

DECLSPEC_IMPORT int WINAPI Msvcrt$isxdigit(int c);
DECLSPEC_IMPORT int WINAPI Msvcrt$isdigit(int c);
DECLSPEC_IMPORT unsigned long WINAPI Msvcrt$strtoul(char *strSource, char **endptr, int base);

DWORD set_regkey(const char * hostname, HKEY hive, const char * path, const char * key, DWORD type, const BYTE * data, DWORD datalen) {
	DWORD dwresult = ERROR_SUCCESS;
	HKEY rootkey = NULL;
	HKEY RemoteKey = NULL;
	HKEY targetkey = NULL;

	if (! hostname) {
		dwresult = Advapi32$RegOpenKeyExA(hive, NULL, 0, KEY_WRITE, &rootkey);
		if (dwresult != ERROR_SUCCESS) {
			BadgerDispatch(g_dispatch, "[-] Error RegOpenKeyExA: %lx\n", dwresult); 
			goto set_regkey_end;
		}
	} else {
		dwresult = Advapi32$RegConnectRegistryA(hostname, hive, &RemoteKey);
		if (dwresult != ERROR_SUCCESS) {
			BadgerDispatch(g_dispatch, "[-] Error RegConnectRegistryA: %lx\n", dwresult); 
			goto set_regkey_end;
		}
		dwresult = Advapi32$RegOpenKeyExA(RemoteKey, NULL, 0, KEY_WRITE, &rootkey);
		if (ERROR_SUCCESS != dwresult) {
			BadgerDispatch(g_dispatch, "[-] Error RegOpenKeyExA: %lx\n", dwresult); 
			goto set_regkey_end;
		}
	}
	dwresult = Advapi32$RegCreateKeyExA(rootkey,path,0,NULL,0,KEY_WRITE,NULL,&targetkey,NULL);
	if (ERROR_SUCCESS != dwresult) {
		BadgerDispatch(g_dispatch, "[-] Error RegCreateKeyExA: %lx\n", dwresult); 
		goto set_regkey_end;
	}
	dwresult = Advapi32$RegSetValueExA(targetkey, key, 0, type, data, datalen);
	if (ERROR_SUCCESS != dwresult) {
		BadgerDispatch(g_dispatch, "[-] Error RegSetValueExA: %lx\n", dwresult); 
		goto set_regkey_end;
	}
	BadgerDispatch(g_dispatch, "[+] Success\n");

set_regkey_end:
	if (RemoteKey) {
		Advapi32$RegCloseKey(RemoteKey);
		rootkey = NULL;
	}
	if (rootkey) {
		Advapi32$RegCloseKey(rootkey);
		rootkey = NULL;
	}
	if (targetkey) {
		Advapi32$RegCloseKey(targetkey);
		targetkey = NULL;
	}
	return dwresult;
}

int is_hex(char *str) {
    if (BadgerStrlen(str) > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        for (int i = 2; str[i] != '\0'; i++) {
            if (!Msvcrt$isxdigit((unsigned char)str[i])) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int is_number(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!Msvcrt$isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

void coffee(char *argv[], int argc, WCHAR** dispatch) {
	DWORD dwErrorCode = ERROR_SUCCESS;
	LPCSTR lpszHostName = NULL;
	HKEY hkRootKey = NULL;
	CHAR* hkey = NULL;
	LPCSTR lpszRegPathName = NULL;
	LPCSTR lpszRegValueName = NULL;
	DWORD dwType = REG_SZ;
	DWORD dwRegData = 0;
	CHAR* dwStrRegData = NULL;
	DWORD dwRegDataLength = 0;
	CHAR* option = NULL;
	g_dispatch = dispatch;

	if (argc != 6) {
        BadgerDispatch(dispatch, "[!] Usage: reg_set.o <Registry Hive> <Hostname> <Registry Path> <Registry Key Value> [-h|-i|-a] <Registry Key Data>\n NOTE:\n 1. Specify Registry hive as follows, HKEY_CLASSES_ROOT as HKCR, HKEY_CURRENT_USER as HKCU, HKEY_LOCAL_MACHINE as HKLM, HKEY_USERS as HKU and HKEY_CURRENT_CONFIG as HKCC \n 2. Use empty string \"\" or NULL for no path. \n 3. Keep hostname 'localhost' for local machine\n 4. Specify -h option for hex data, -i for integer data, -a for ascii data for the registry key data of key Value\n 5. E.g.: reg-set.o HKCU localhost \"Uninstall\\Test\" TestVal -h 0xefcdcdcd\n");
        return;
    }
	hkey = argv[0];
	if (BadgerStrcmp(hkey, "HKCR") == 0) {
		hkRootKey = HKEY_CLASSES_ROOT;
		hkey = "HKEY_CLASSES_ROOT";
	} else if (BadgerStrcmp(hkey, "HKCU") == 0) {
		hkRootKey = HKEY_CURRENT_USER;
		hkey = "HKEY_CURRENT_USER";
	} else if (BadgerStrcmp(hkey, "HKLM") == 0) {
		hkRootKey = HKEY_LOCAL_MACHINE;
		hkey = "HKEY_LOCAL_MACHINE";
	} else if (BadgerStrcmp(hkey, "HKU") == 0) {
		hkRootKey = HKEY_USERS;
		hkey = "HKEY_USERS";
	} else if (BadgerStrcmp(hkey, "HKCC") == 0) {
		hkRootKey = HKEY_CURRENT_CONFIG;
		hkey = "HKEY_CURRENT_CONFIG";
	} else {
		BadgerDispatch(dispatch, " [-] Invalid option. Select one of the following: HKEY_CLASSES_ROOT as HKCR, HKEY_CURRENT_USER as HKCU, HKEY_LOCAL_MACHINE as HKLM, HKEY_USERS as HKU and HKEY_CURRENT_CONFIG as HKCC\n");
		return;
	}
	lpszHostName = argv[1];
	BadgerDispatch(dispatch, "[*] Hostname: %s\n", lpszHostName);
	if (BadgerStrcmp(lpszHostName, "localhost") == 0) {
		lpszHostName = NULL;
	}
	lpszRegPathName = argv[2];
	if (lpszRegPathName == NULL || lpszRegPathName[0] == '\0' || BadgerStrcmp(lpszRegPathName, "NULL") == 0) {
		lpszRegPathName = NULL;
	}
	BadgerDispatch(dispatch, "[*] Registry path: %s\n", lpszRegPathName);
	lpszRegValueName = argv[3];
	if (lpszRegValueName == NULL || lpszRegValueName[0] == '\0' || BadgerStrcmp(lpszRegValueName, "NULL") == 0) {
		lpszRegValueName = NULL;
	}
	BadgerDispatch(dispatch, "[*] Registry value: %s\n", lpszRegValueName);
	option = argv[4];
	BadgerDispatch(dispatch, "[*] Option: %s\n", option);
	dwStrRegData = argv[5];
	BadgerDispatch(dispatch, "[*] Registry data: %s\n", dwStrRegData);
	if (BadgerStrcmp(option, "-h") == 0) {
		if (is_hex(dwStrRegData)) {
			dwRegData = Msvcrt$strtoul(dwStrRegData, NULL, 16);
			dwType = REG_DWORD;
			dwRegDataLength = sizeof(DWORD);
		}
	} else if (BadgerStrcmp(option, "-i") == 0) {
		if (is_number(dwStrRegData)) {
			dwRegData = Msvcrt$strtoul(dwStrRegData, NULL, 10);
			dwType = REG_DWORD;
			dwRegDataLength = sizeof(DWORD);
		}
	} else if (BadgerStrcmp(option, "-a") == 0) {
		dwRegDataLength = BadgerStrlen(dwStrRegData)+1;
	} else {
		BadgerDispatch(dispatch, "[-] Invalid option. Select '-h' for hex data, '-i' for numeric data, and '-a' for ASCII data\n");
		return;
	}
	BadgerDispatch(dispatch, "[*] Setting registry key: %s\\%s\\%s => %s => %s\n", ((lpszHostName == NULL) ? "\\\\." : lpszHostName), hkey, lpszRegPathName, lpszRegValueName, dwStrRegData);
	LPBYTE regData = dwStrRegData;
	if (dwType == REG_DWORD) {
		regData = (LPBYTE)&dwRegData;
	}
	dwErrorCode = set_regkey(lpszHostName, hkRootKey, lpszRegPathName, lpszRegValueName, dwType, regData, dwRegDataLength);
	if (dwErrorCode != ERROR_SUCCESS) {
		BadgerDispatch(dispatch, "[-] Failed\n");
	}

    if (hkRootKey) {
		Advapi32$RegCloseKey(hkRootKey);
	}
	return;
}
