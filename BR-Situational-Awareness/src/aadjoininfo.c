#include "common.h"


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

void GetAadJoinInfo() {
    DWORD res;
	PDSREG_JOIN_INFO pJoinInfo;
	res = NetGetAadJoinInformation(NULL, &pJoinInfo);

    if (res == 0)
	{
		PRINT("\n================== AAD/Entra ID Join Info ==================\n");
		switch (pJoinInfo->joinType)
		{
			case DSREG_DEVICE_JOIN:
				PRINT("%-20s: %s\n", "Join Type", "Device join");
				break;
			case DSREG_WORKPLACE_JOIN:
				PRINT("%-20s: %s\n", "Join Type", "Workplace join");
				break;
			default:
				PRINT("%-20s: %s\n", "Join Type", "Unknown");
				break;
		}
		PRINT("%-20s: %S\n", "Device ID", pJoinInfo->pszDeviceId);
		PRINT("%-20s: %S\n", "IDP Domain", pJoinInfo->pszIdpDomain);
		PRINT("%-20s: %S\n", "Tenant ID", pJoinInfo->pszTenantId);
		PRINT("%-20s: %S\n", "Tenant Display Name", pJoinInfo->pszTenantDisplayName);
		PRINT("%-20s: %S\n", "Join User Email", pJoinInfo->pszJoinUserEmail);
		//PRINT("%-20s: %S\n", "MDM Enrollment URL", pJoinInfo->pszMdmEnrollmentUrl);
		//PRINT("%-20s: %S\n", "MDM Terms of Use URL", pJoinInfo->pszMdmTermsOfUseUrl);
		//PRINT("%-20s: %S\n", "MDM Compliance URL", pJoinInfo->pszMdmComplianceUrl);
		//PRINT("%-20s: %S\n", "User Setting Sync URL", pJoinInfo->pszUserSettingSyncUrl);
		
		//
		// Only get join user info if type is DSREG_DEVICE_JOIN
		//
		
		if (((DSREG_JOIN_TYPE)(pJoinInfo->joinType) == (DSREG_JOIN_TYPE)DSREG_DEVICE_JOIN) && (pJoinInfo->pUserInfo != NULL))
		{
			PRINT("\n====================== Join User Info ======================\n");
			PRINT("%-20s: %S\n", "User Email", pJoinInfo->pUserInfo->pszUserEmail);
			PRINT("%-20s: %S\n", "User Key ID", pJoinInfo->pUserInfo->pszUserKeyId);
			
			//
			// Extract User SID from pszUserKeyName
			//

			// PRINT("%-20s: %S\n", "User Key Name", pJoinInfo->pUserInfo->pszUserKeyName);
			if (pJoinInfo->pUserInfo->pszUserKeyName != NULL)
			{
				WCHAR userSid[256] = {0};
				WCHAR *slashPos = wcschr(pJoinInfo->pUserInfo->pszUserKeyName, L'/');
				if (slashPos != NULL)
				{
					size_t sidLength = (size_t)(slashPos - pJoinInfo->pUserInfo->pszUserKeyName);
					wcsncpy_s(userSid, sizeof(userSid) / sizeof(WCHAR), pJoinInfo->pUserInfo->pszUserKeyName, sidLength);
					PRINT("%-20s: %S\n", "User SID", userSid);
				}
			}
		} else {
			EPRINT("\n[-] Join user info was null or host is not device joined\n");
		}	
	
	//
	// NetGetAadJoinInformation failed 
	//
	} else {
		PRINT("[-] Error: %d\n", res);
		PRINT("[-] Host may not be cloud joined\n");
	}

	//
	// Free the join info
	//
	if (pJoinInfo != NULL)
	{
		NetFreeAadJoinInformation(pJoinInfo);
	}
}

void coffee(char** argv, int argc, WCHAR** dispatch) {
    g_dispatch = dispatch;
    GetAadJoinInfo();
}