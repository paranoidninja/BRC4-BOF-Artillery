#pragma once
#include "common.h"

#ifndef __MSVCRT_H__
#define __MSVCRT_H__

#define intZeroMemory(addr,size) Msvcrt$memset((addr),0,size)

// Headers to make life easier
#define _msize                  Msvcrt$_msize
// #define _localtime32_s          Msvcrt$_localtime32_s
#define _snprintf               Msvcrt$_snprintf
#define _snwprintf              Msvcrt$_snwprintf
#define _snwprintf_s            Msvcrt$_snwprintf_s
#define _strdup                 Msvcrt$_strdup
#define _stricmp                Msvcrt$_stricmp
#define _strnicmp               Msvcrt$_strnicmp
#define _wcsicmp                Msvcrt$_wcsicmp

// #define asctime_s               Msvcrt$asctime_s

#define calloc                  Msvcrt$calloc
#define ceil                    Msvcrt$ceil

#define isdigit                 Msvcrt$isdigit

#define free                    Msvcrt$free

#define malloc                  Msvcrt$malloc
#define mbstowcs                Msvcrt$mbstowcs
#define memcpy                  Msvcrt$memcpy
#define memset                  Msvcrt$memset

#define realloc                 Msvcrt$realloc

#define sprintf_s               Msvcrt$sprintf_s
#define strcat_s                Msvcrt$strcat_s
#define strcpy                  Msvcrt$strcpy
#define strlen                  Msvcrt$strlen
#define strncat                 Msvcrt$strncat
#define strstr                  Msvcrt$strstr
#define strtok                  Msvcrt$strtok
#define strtol                  Msvcrt$strtol
#define strtoul                 Msvcrt$strtoul
#define swprintf                Msvcrt$swprintf
#define strcat                  Msvcrt$strcat

#define towlower                Msvcrt$towlower

#define wcscat                  Msvcrt$wcscat
#define wcschr                  Msvcrt$wcschr
#define wcsncat                 Msvcrt$wcsncat
#define wcscmp                  Msvcrt$wcscmp
#define wcslen                  Msvcrt$wcslen
#define wcsncpy                 Msvcrt$wcsncpy
#define wcsstr                  Msvcrt$wcsstr
#define wcsncpy_s               Msvcrt$wcsncpy_s

// Actual function definitions
WINADVAPI WINAPI size_t     Msvcrt$_msize(void *memblock);
// WINADVAPI WINAPI errno_t    Msvcrt$_localtime32_s(struct tm* tmDest, __time32_t const* sourceTime);
WINADVAPI WINAPI int        Msvcrt$_snprintf(char *buffer, size_t count, const char *__format,  ...);
WINADVAPI WINAPI int        Msvcrt$_snwprintf(wchar_t *buffer, size_t count, const wchar_t *format, ...);
WINADVAPI WINAPI int        Msvcrt$_snwprintf_s(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format , ...);
WINADVAPI WINAPI char *     Msvcrt$_strdup(const char *strSource);
WINADVAPI WINAPI int 	    Msvcrt$_stricmp(const char *string1, const char *string2);
WINADVAPI WINAPI int        Msvcrt$_strnicmp(const char *string1,const char *string2, size_t count);

WINADVAPI WINAPI int 	    Msvcrt$_wcsicmp(const wchar_t *string1, const wchar_t *string2);

// WINADVAPI WINAPI errno_t    Msvcrt$asctime_s(char* buffer, size_t numberOfElements, const struct tm *tmSource);

WINADVAPI WINAPI VOID*      Msvcrt$calloc(size_t number, size_t size);
WINADVAPI WINAPI double     Msvcrt$ceil(double x);
WINADVAPI WINAPI VOID       Msvcrt$free(void *_Memory);

WINADVAPI WINAPI int        Msvcrt$isdigit(int c);

WINADVAPI WINAPI VOID*      Msvcrt$malloc(size_t _SizeOfElements);
WINADVAPI WINAPI size_t     Msvcrt$mbstowcs(wchar_t *wcstr, const char *mbstr, size_t count);
WINADVAPI WINAPI void*      Msvcrt$memcpy(void *dest, const void *src, size_t count);
WINADVAPI WINAPI void*      Msvcrt$memset(void *dest, int c, size_t count);

WINADVAPI WINAPI VOID*      Msvcrt$realloc(void *memblock, size_t size);

WINADVAPI WINAPI int            Msvcrt$sprintf_s(char *_DstBuf, size_t _DstSize, const char *_Format, ...);
WINADVAPI WINAPI errno_t        Msvcrt$strcat_s(char *_Dst, rsize_t _SizeInBytes, const char * _Src);

WINADVAPI WINAPI char *         Msvcrt$strcat(char *strDestination, const char *strSource);

WINADVAPI WINAPI char*          Msvcrt$strcpy(char * __restrict__ __dst, const char * __restrict__ __src);
WINADVAPI WINAPI char*          Msvcrt$strstr(char* __s1, const char* __s2);
WINADVAPI WINAPI char*          Msvcrt$strtok(char * __restrict__ _Str,const char * __restrict__ _Delim);
WINADVAPI WINAPI int            Msvcrt$swprintf(wchar_t *buffer, size_t count, const wchar_t *format , ...);
WINADVAPI WINAPI unsigned long  Msvcrt$strtoul(const char *strSource, char **endptr, int base);
WINADVAPI WINAPI long           Msvcrt$strtol(const char *string, char **end_ptr, int base);
WINADVAPI WINAPI size_t         Msvcrt$strlen(const char *str);
WINADVAPI WINAPI char *         Msvcrt$strncat(char *strDest, const char *strSource, size_t count);

WINADVAPI WINAPI int        Msvcrt$towlower(wint_t c);

WINADVAPI WINAPI wchar_t *  Msvcrt$wcscat(wchar_t *strDestination, const wchar_t *strSource);
WINADVAPI WINAPI wchar_t *  Msvcrt$wcschr(const wchar_t *str, wchar_t c);
WINADVAPI WINAPI int        Msvcrt$wcscmp(const wchar_t *string1, const wchar_t *string2);
WINADVAPI WINAPI size_t     Msvcrt$wcslen(const wchar_t *str);
WINADVAPI WINAPI wchar_t *  Msvcrt$wcsncpy(wchar_t *strDest, const wchar_t *strSource, size_t count);
WINADVAPI WINAPI wchar_t *  Msvcrt$wcsncat(wchar_t *strDest, const wchar_t *strSource, size_t count);
WINADVAPI WINAPI wchar_t*   Msvcrt$wcsstr(const wchar_t *str, const wchar_t *strSearch);
WINADVAPI WINAPI errno_t    Msvcrt$wcsncpy_s(wchar_t *strDest, size_t numberOfElements, const wchar_t *strSource, size_t count);

#endif
