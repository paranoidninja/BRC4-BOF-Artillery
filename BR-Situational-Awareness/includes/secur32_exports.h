#include <sspi.h>

WINADVAPI WINAPI SECURITY_STATUS SEC_ENTRY Secur32$FreeCredentialsHandle(PCredHandle phCredential);
WINADVAPI WINAPI SECURITY_STATUS SEC_ENTRY Secur32$AcquireCredentialsHandleA(LPSTR pszPrincipal, LPSTR pszPackage, unsigned long fCredentialUse, void *pvLogonId, void *pAuthData, SEC_GET_KEY_FN pGetKeyFn, void *pvGetKeyArgument, PCredHandle phCredential, PTimeStamp ptsExpiry);
WINADVAPI WINAPI SECURITY_STATUS SEC_ENTRY Secur32$InitializeSecurityContextA(PCredHandle phCredential, PCtxtHandle phContext, SEC_CHAR *pszTargetName, unsigned long fContextReq, unsigned long Reserved1, unsigned long TargetDataRep, PSecBufferDesc pInput, unsigned long Reserved2, PCtxtHandle phNewContext, PSecBufferDesc pOutput, unsigned long *pfContextAttr, PTimeStamp ptsExpiry);
