#pragma once
#include "common.h"

// Project specific exports
WINADVAPI WINAPI VOID    Ole32$CoUninitialize();
WINADVAPI WINAPI HRESULT Ole32$CoInitializeEx(LPVOID, DWORD);
WINADVAPI WINAPI HRESULT Ole32$CoCreateInstance(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID*);
WINADVAPI WINAPI HRESULT Ole32$CoInitializeSecurity(PSECURITY_DESCRIPTOR pSecDesc, LONG cAuthSvc, SOLE_AUTHENTICATION_SERVICE *asAuthSvc, void *pReserved1, DWORD dwAuthnLevel, DWORD dwImpLevel, void *pAuthList, DWORD dwCapabilities, void *pReserved3);

DECLSPEC_IMPORT void    WINAPI Ole32$CoTaskMemFree(LPVOID pv);
DECLSPEC_IMPORT HRESULT WINAPI Ole32$CLSIDFromString(LPCOLESTR lpsz, LPCLSID pclsid);
DECLSPEC_IMPORT HRESULT WINAPI Ole32$IIDFromString(LPCOLESTR lpsz, LPIID lpiid);

WINADVAPI WINAPI VOID    OleAut32$SysFreeString(BSTR);
WINADVAPI WINAPI HRESULT OleAut32$VariantClear(VARIANTARG *pvarg);
WINADVAPI WINAPI BSTR    OleAut32$SysAllocString(const OLECHAR *);

const CLSID CLSID_TraceSession = {0x0383751c, 0x098b, 0x11d8, {0x94, 0x14, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30}}; 
const IID IID_IDataCollectorSet = {0x03837520, 0x098B, 0x11D8, {0x94, 0x14, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30}};

const CLSID CLSIDWbemLocator = {0x4590F811, 0x1D3A, 0x11D0, {0x89, 0x1F, 0, 0xAA, 0, 0x4B, 0x2E, 0x24}};
const GUID  IIDIWbemLocator = {0xDC12A687, 0x737F, 0x11CF, { 0x88, 0x4D, 0x00, 0xAA, 0x00, 0x4B, 0x2E, 0x24 }};
