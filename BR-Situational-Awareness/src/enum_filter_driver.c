#include "common.h"

#define SZ_SERVICE_KEY "a"
#define SZ_INSTANCE_KEY "Instances"
#define SZ_ALTITUDE_VALUE "Altitude"

void usage() {
    PRINT("[+] Usage:\n");
    PRINT("      enum_filter_driver HOSTNAME\n\n");
    PRINT("[+] Description:\n");
    PRINT("      Enumerate filter drivers on a particular host. If no hostname is specified, it enumerates the local machine. The name of the remote computer. The string has the following form:\n      \\\\computername");
}

void Enum_Filter_Driver(LPCSTR szHostName) {
    DWORD dwErrorCode = 0;
    HKEY hRootKey = NULL;
    HKEY hRemoteKey = NULL;
    HKEY hServiceKey = NULL;
    HKEY hInstanceKey = NULL;
    HKEY hInstanceSubkey = NULL;

    LPSTR szServiceKeyName = NULL;
    DWORD dwServiceKeyNameCount = MAX_PATH;
    DWORD dwServiceKeyIndex = 0;
    LPSTR szInstancesSubkeyName = NULL;
    DWORD dwInstancesSubkeyNameCount = MAX_PATH;
    DWORD dwInstancesSubkeyIndex = 0;
    LPSTR szAltitudeValue = NULL;
    DWORD dwAltitudeValue = 0;
    DWORD dwAltitudeValueType = 0;
    DWORD dwAltitudeValueCount = MAX_PATH;

    LSTATUS status = 0;

    do {
        // Allocate memory
        szServiceKeyName = (LPSTR)intAlloc(MAX_PATH);
        if (szServiceKeyName == NULL) {
            INTALLOC_E;
            break;
        }
        intZeroMemory(szServiceKeyName, MAX_PATH);

        szInstancesSubkeyName = (LPSTR)intAlloc(MAX_PATH);
        if (szInstancesSubkeyName == NULL) {
            INTALLOC_E;
            break;
        }
        intZeroMemory(szInstancesSubkeyName, MAX_PATH);

        szAltitudeValue = (LPSTR)intAlloc(MAX_PATH);
        if (szAltitudeValue == NULL) {
            INTALLOC_E;
            break;
        }
        intZeroMemory(szAltitudeValue, MAX_PATH);

        // open root key
        if (szHostName != NULL) {
            PRINT("[+] Enumerating Host: %s\n", szHostName);
            status = RegConnectRegistryA(szHostName, HKEY_LOCAL_MACHINE, &hRemoteKey);
            if (dwErrorCode != ERROR_SUCCESS) {
                NTEPRINT("RegConnectRegistryA", status);
                break;
            }
            PRINT("[+] Establishes a connection to a predefined registry key on %s\n", szHostName);
        } else {
            PRINT("[+] Enumerating current host\n");
        }

        status = RegOpenKeyExA(
            (szHostName == NULL)? HKEY_LOCAL_MACHINE: hRemoteKey,
            SZ_SERVICE_KEY, 0, KEY_READ,
            &hRootKey
        );
        if (status != ERROR_SUCCESS) {
            NTEPRINT("RegOpenKeyExA", status);
            break;
        }

        PRINT("\n");

        // loop through all service subkeys
        status = RegEnumKeyExA(
            hRootKey,          // Root key
            dwServiceKeyIndex,
            szServiceKeyName,
            &dwServiceKeyNameCount,
            NULL,
            NULL,
            NULL,
            NULL);

        while ( status != ERROR_NO_MORE_ITEMS ) {
            // Open service subkey
            status = RegOpenKeyExA(
                hRootKey,
                szServiceKeyName,
                0,
                KEY_READ,
                &hServiceKey
            );
            if (status == ERROR_SUCCESS) {

                // open service subkey's Instances subkey
                status = RegOpenKeyExA(hServiceKey, SZ_INSTANCE_KEY, 0, KEY_READ, &hInstanceKey);
                if (status == ERROR_SUCCESS) {
                    // loop through all instances subkeys

                    dwInstancesSubkeyIndex = 0;
                    status = RegEnumKeyExA(hInstanceKey, dwInstancesSubkeyIndex, szInstancesSubkeyName, &dwInstancesSubkeyNameCount, NULL, NULL, NULL, NULL);

                    while ( status != ERROR_NO_MORE_ITEMS ) {
                        // open instances subkey
                        status = RegOpenKeyExA(hInstanceKey, szInstancesSubkeyName, 0, KEY_READ, &hInstanceSubkey);
                        if (ERROR_SUCCESS == status) {
                            // query for altitude value
                            status = RegQueryValueExA(hInstanceSubkey, SZ_ALTITUDE_VALUE, NULL, &dwAltitudeValueType, (unsigned char*)szAltitudeValue, &dwAltitudeValueCount);
                            if (ERROR_SUCCESS == status) {
                                // PRINT("[+] Opened service subkey: %s\n", szServiceKeyName);
                                // PRINT("[+] Opened instances subkey: %s\n", szInstancesSubkeyName);
                                dwAltitudeValue = strtoul(szAltitudeValue, NULL, 10);

                                // See: https://learn.microsoft.com/en-us/windows-hardware/drivers/ifs/allocated-altitudes
                                if ( (dwAltitudeValue >= 360000) && (dwAltitudeValue <= 389999)) PRINT("[+] activitymonitor [Service Name: %s, Altitude: %lu]\n", szServiceKeyName, dwAltitudeValue);
                                if ( (dwAltitudeValue >= 320000) && (dwAltitudeValue <= 329999)) PRINT("[+] antivirus [Service Name: %s, Altitude: %lu]\n", szServiceKeyName, dwAltitudeValue);
                                if ( (dwAltitudeValue >= 260000) && (dwAltitudeValue <= 269999) ) PRINT("[+] contentscreener [Service Name: %s, Altitude: %lu]\n", szServiceKeyName, dwAltitudeValue);
                            }

                            else {
                                NTEPRINT("RegQueryValueExA", status);
                            }

                            intZeroMemory(szAltitudeValue, MAX_PATH);
                            dwAltitudeValueCount = MAX_PATH;
                        }// end if open instances subkey was successful

                        else {
                            NTEPRINT("RegOpenKeyExA", status);
                        } // end else open instances subkey failed

                        if ( hInstanceSubkey ) { RegCloseKey(hInstanceSubkey); hInstanceSubkey = NULL; }

                        intZeroMemory(szInstancesSubkeyName, MAX_PATH);
                        dwInstancesSubkeyNameCount = MAX_PATH;

                        dwInstancesSubkeyIndex++;
                        status = RegEnumKeyExA(hInstanceKey, dwInstancesSubkeyIndex, szInstancesSubkeyName, &dwInstancesSubkeyNameCount, NULL, NULL, NULL, NULL);
                    } // end loop through all instances subkeys

                    if ( hInstanceSubkey ) { RegCloseKey(hInstanceSubkey); hInstanceSubkey = NULL; }

                } // end if open service subkey's Instances subkey was successful

                if ( hInstanceKey ) { RegCloseKey(hInstanceKey); hInstanceKey = NULL; }
            } // end if open service subkey was successful
            else {
                NTEPRINT("RegOpenKeyExA", status);
            } // end else open service subkey failed

            if ( hServiceKey ) { RegCloseKey(hServiceKey); hServiceKey = NULL; }

            intZeroMemory(szServiceKeyName, MAX_PATH);
            dwServiceKeyNameCount = MAX_PATH;

            dwServiceKeyIndex++;
            status = RegEnumKeyExA(hRootKey, dwServiceKeyIndex, szServiceKeyName, &dwServiceKeyNameCount, NULL, NULL, NULL, NULL);
        }
    } while(FALSE);

    if (status == ERROR_NO_MORE_ITEMS) PRINT("\n[+] Parsed all registry keys!\n");


    // cleanup here
    if (szAltitudeValue)        intFree(szAltitudeValue);
    if (szInstancesSubkeyName)  intFree(szInstancesSubkeyName);
    if (szServiceKeyName)       intFree(szServiceKeyName);

    if (hInstanceSubkey)        RegCloseKey(hInstanceSubkey);
    if (hInstanceKey)           RegCloseKey(hInstanceKey);
    if (hServiceKey)            RegCloseKey(hServiceKey);
    if (hRootKey)               RegCloseKey(hRootKey);
    if (hRemoteKey)             RegCloseKey(hRemoteKey);

}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;

    LPCSTR szHostName = NULL;

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

    if (argc > 1) {
        usage();
        return;
    }

    if (argc == 1) {
        szHostName = argv[0];
    }

    Enum_Filter_Driver(szHostName);

}
