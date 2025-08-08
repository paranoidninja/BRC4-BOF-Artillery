#pragma once 
#include "common.h"

#define GetFileVersionInfoW         Version$GetFileVersionInfoW
#define GetFileVersionInfoSizeW     Version$GetFileVersionInfoSizeW
#define VerQueryValueA              Version$VerQueryValueA

WINADVAPI WINAPI BOOL     Version$GetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
WINADVAPI WINAPI DWORD    Version$GetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle);
WINADVAPI WINAPI BOOL     Version$VerQueryValueA(LPCVOID pBlock, LPCSTR  lpSubBlock, LPVOID  *lplpBuffer, PUINT puLen);
