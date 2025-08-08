#include "badger_exports.h" 
#include <ntsecapi.h>
#pragma once

#ifndef SAM_SERVER_LOOKUP_DOMAIN
#define SAM_SERVER_LOOKUP_DOMAIN 0x00000020
#endif 


typedef enum _USER_INFORMATION_CLASS {
	UserResetInformation = 30
} USER_INFORMATION_CLASS, * PUSER_INFORMATION_CLASS;

typedef struct _USER_RESET_INFORMATION {
	ULONG ExtendedWhichFields;
	UNICODE_STRING ResetData;
} USER_RESET_INFORMATION, * PUSER_RESET_INFORMATION;

typedef PVOID SAM_HANDLE, * PSAM_HANDLE;

__declspec(dllimport) __stdcall NTSTATUS Samlib$SamConnect(PUNICODE_STRING, PSAM_HANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
__declspec(dllimport) __stdcall NTSTATUS Samlib$SamOpenDomain(SAM_HANDLE, ACCESS_MASK, PSID, PSAM_HANDLE);
__declspec(dllimport) __stdcall NTSTATUS Samlib$SamOpenUser(SAM_HANDLE, ACCESS_MASK, ULONG, PSAM_HANDLE);
__declspec(dllimport) __stdcall NTSTATUS Samlib$SamQueryInformationUser(SAM_HANDLE, USER_INFORMATION_CLASS, PVOID);
__declspec(dllimport) __stdcall NTSTATUS Samlib$SamCloseHandle(SAM_HANDLE);
