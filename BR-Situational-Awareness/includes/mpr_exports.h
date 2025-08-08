#pragma once
#include "common.h"

__declspec(dllimport) __stdcall DWORD 	Mpr$WNetGetConnectionA(LPCSTR lpLocalName, LPSTR lpRemoteName, LPDWORD lpnLength);
__declspec(dllimport) __stdcall DWORD  	Mpr$WNetAddConnection2A(LPNETRESOURCEA lpNetResource, LPCSTR lpPassword, LPCSTR lpUserName, DWORD dwFlags);
