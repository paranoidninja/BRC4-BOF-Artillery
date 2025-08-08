#include <windows.h>
#include <windns.h>

typedef struct _DNS_CACHE_ENTRY {
    struct _DNS_CACHE_ENTRY* pNext; // Pointer to next entry
    PWSTR pszName; // DNS Record Name
    unsigned short wType; // DNS Record Type
    unsigned short wDataLength; // Not referenced
    unsigned long dwFlags; // DNS Record Flags
} DNSCACHEENTRY, *PDNSCACHEENTRY;


WINADVAPI WINAPI void  Dnsapi$DnsFree(PVOID pData, DNS_FREE_TYPE FreeType);
WINADVAPI WINAPI DWORD Dnsapi$DnsGetCacheDataTableEx(ULONG64 Flags, DNSCACHEENTRY** ppTable);
//WINADVAPI WINAPI DWORD Dnsapi$DnsGetCacheDataTable(DNSCACHEENTRY** ppTable);
// WINADVAPI WINAPI int Dnsapi$DnsGetCacheDataTable(PDNSCACHEENTRY ppTable);