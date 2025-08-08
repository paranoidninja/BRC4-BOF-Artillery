#pragma once
#include "common.h"

#define NetGetAadJoinInformation  NETAPI32$NetGetAadJoinInformation
#define NetFreeAadJoinInformation NETAPI32$NetFreeAadJoinInformation

typedef enum _DSREG_JOIN_TYPE{
    DSREG_UNKNOWN_JOIN = 0,
    DSREG_DEVICE_JOIN = 1,
    DSREG_WORKPLACE_JOIN = 2
} DSREG_JOIN_TYPE, *PDSREG_JOIN_TYPE;

typedef struct _DSREG_USER_INFO
{
    LPWSTR pszUserEmail;
    LPWSTR pszUserKeyId;
    LPWSTR pszUserKeyName;

} DSREG_USER_INFO, *PDSREG_USER_INFO;

typedef struct _DSREG_JOIN_INFO
{
    DSREG_JOIN_TYPE joinType;
    PCCERT_CONTEXT pJoinCertificate;
    LPWSTR pszDeviceId;
    LPWSTR pszIdpDomain;
    LPWSTR pszTenantId;
    LPWSTR pszJoinUserEmail;
    LPWSTR pszTenantDisplayName;
    LPWSTR pszMdmEnrollmentUrl;
    LPWSTR pszMdmTermsOfUseUrl;
    LPWSTR pszMdmComplianceUrl;
    LPWSTR pszUserSettingSyncUrl;
    DSREG_USER_INFO *pUserInfo;
} DSREG_JOIN_INFO, *PDSREG_JOIN_INFO;

WINBASEAPI DWORD WINAPI  NETAPI32$NetGetAadJoinInformation(LPCWSTR pcszTenantId, PDSREG_JOIN_INFO *ppJoinInfo);
WINBASEAPI VOID  WINAPI  NETAPI32$NetFreeAadJoinInformation(PDSREG_JOIN_INFO pJoinInfo);
