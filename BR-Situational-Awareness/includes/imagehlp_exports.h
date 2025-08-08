#include "common.h"

#ifndef __IMAGEHLP_H__
#define __IMAGEHLP_H__

#define ImageEnumerateCertificates      Imagehlp$ImageEnumerateCertificates
#define ImageGetCertificateData         Imagehlp$ImageGetCertificateData
#define ImageGetCertificateHeader       Imagehlp$ImageGetCertificateHeader

WINADVAPI WINAPI BOOL Imagehlp$ImageEnumerateCertificates(HANDLE FileHandle, WORD TypeFilter, PDWORD CertificateCount, PDWORD Indices, DWORD IndexCount);
WINADVAPI WINAPI BOOL Imagehlp$ImageGetCertificateHeader(HANDLE FileHandle, DWORD CertificateIndex, LPWIN_CERTIFICATE Certificateheader);
WINADVAPI WINAPI BOOL Imagehlp$ImageGetCertificateData(HANDLE FileHandle, DWORD CertificateIndex, LPWIN_CERTIFICATE Certificate, PDWORD RequiredLength);

#endif
