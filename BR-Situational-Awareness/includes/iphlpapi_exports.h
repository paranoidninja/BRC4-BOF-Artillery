
#pragma once
#include "common.h"

__declspec(dllimport) __stdcall VOID  Iphlpapi$FreeMibTable(PVOID Memory);
__declspec(dllimport) __stdcall ULONG Iphlpapi$GetAdaptersInfo(PIP_ADAPTER_INFO, PULONG);
__declspec(dllimport) __stdcall DWORD Iphlpapi$GetIpNetTable2(ADDRESS_FAMILY Family, PMIB_IPNET_TABLE2 *Table);
__declspec(dllimport) __stdcall DWORD Iphlpapi$GetIpForwardTable (PMIB_IPFORWARDTABLE pIpForwardTable, PULONG pdwSize, WINBOOL bOrder);
