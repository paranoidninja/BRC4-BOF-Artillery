#pragma once 
#include "common.h"

#define PRINT(format, ...) BadgerDispatch(g_dispatch, format, ##__VA_ARGS__)
#define EPRINT PRINT
#define ERR_PRINT(func)     EPRINT("[-] %s() failed at %s:%d with error: %ld\n", func, __FILE__, __LINE__, GetLastError())
#define NTEPRINT(x, status) EPRINT("[-] %s() failed at %s:%d with error: 0x%lx\n", x, __FILE__, __LINE__, status)
#define MALLOC_E            EPRINT("[-] malloc() failed at %s:%d\n", __FILE__, __LINE__);
#define INTALLOC_E          ERR_PRINT("HeapAlloc")
#define DBG                 PRINT("[+] WORKS AT %s:%d\n", __FILE__, __LINE__);
