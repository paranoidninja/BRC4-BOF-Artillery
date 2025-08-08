#pragma once
#include "common.h"

#ifndef __CRYPT_H__
#define __CRYPT_H__

#define CertGetNameStringW                      Crypt32$CertGetNameStringW
#define CryptVerifyMessageSignature             Crypt32$CryptVerifyMessageSignature
#define CertFreeCertificateContext              Crypt32$CertFreeCertificateContext

__declspec(dllimport) __stdcall BOOL    Crypt32$CryptUnprotectData(DATA_BLOB *pDataIn, LPWSTR *ppszDataDescr, DATA_BLOB *pOptionalEntropy, PVOID pvReserved, CRYPTPROTECT_PROMPTSTRUCT *pPromptStruct, DWORD dwFlags, DATA_BLOB *pDataOut);
__declspec(dllimport) __stdcall BOOL    Crypt32$CryptVerifyMessageSignature(PCRYPT_VERIFY_MESSAGE_PARA pVerifyPara, DWORD dwSignerIndex, const BYTE *pbSignedBlob, DWORD cbSignedBlob, BYTE *pbDecoded, DWORD *pcbDecoded, PCCERT_CONTEXT *ppSignerCert);
__declspec(dllimport) __stdcall DWORD   Crypt32$CertGetNameStringW(PCCERT_CONTEXT pCertContext, DWORD dwType, DWORD dwFlags, void *pvTypePara, LPWSTR pszNameString, DWORD cchNameString);
__declspec(dllimport) __stdcall BOOL    Crypt32$CertFreeCertificateContext(PCCERT_CONTEXT pCertContext);

#endif
