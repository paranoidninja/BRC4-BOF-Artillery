#include "common.h"

#define BUFFER_SIZE 85

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;

	WCHAR name[BUFFER_SIZE]         = {0};
    WCHAR wcBuffer[BUFFER_SIZE]     = {0};
	WCHAR sysTime[BUFFER_SIZE]      = {0};
	WCHAR geoid[BUFFER_SIZE]        = {0};

    if (GetSystemDefaultLocaleName(name, BUFFER_SIZE) == 0) {
        ERR_PRINT("GetSystemDefaultLocaleName");
        return;
    }

	if(GetLocaleInfoEx(name, LOCALE_SENGLANGUAGE, wcBuffer, BUFFER_SIZE) == 0) {
		ERR_PRINT("GetLocaleInfoEx");
        return;
	}

    LCID lcid = LocaleNameToLCID(name, 0);
    if (lcid == 0) {
        ERR_PRINT("LocaleNameToLCID");
        return;
    }

    if (GetDateFormatEx(name, DATE_LONGDATE, NULL, NULL, sysTime, BUFFER_SIZE, NULL) == 0) {
        ERR_PRINT("GetDateFormatEx");
        return;
    }

    if (GetLocaleInfoEx(name, LOCALE_SLOCALIZEDCOUNTRYNAME, geoid, BUFFER_SIZE) == 0) {
        ERR_PRINT("GetLocaleInfoEx");
        return;
    }

    PRINT("[+] Locale: %S (%S)\n[+] LCID: %x\n[+] Date: %S\n[+] Country: %S\n", wcBuffer, name, lcid, sysTime, geoid); 	
}