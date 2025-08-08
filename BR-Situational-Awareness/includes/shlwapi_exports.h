#pragma once
#include "common.h"

#ifndef __SHLWAPI_H__
#define  __SHLWAPI_H__

#define PathFindFileNameW       Shlwapi$PathFindFileNameW
#define StrStrIA                Shlwapi$StrStrIA


WINADVAPI WINAPI LPCWSTR            Shlwapi$PathFindFileNameW(LPCWSTR pszPath);
WINADVAPI WINAPI PCSTR              Shlwapi$StrStrIA(PCSTR pszFirst, PCSTR pszSrch);

#endif