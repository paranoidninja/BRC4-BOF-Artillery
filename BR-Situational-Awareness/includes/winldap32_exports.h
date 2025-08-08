#define SECURITY_WIN32
#include <windows.h>
#include <security.h>
#include <winldap.h>
#pragma once

#define LDAP_PORT 389
#define LDAPS_PORT 636

WINLDAPAPI LDAP *LDAPAPI Wldap32$ldap_initA(const PSTR HostName, ULONG PortNumber);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_get_optionA(LDAP *ld, int option, void *invalue);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_connect(LDAP *ld, LDAP_TIMEVAL *timeout);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_sasl_bind_sA(LDAP *ExternalHandle, const PSTR DistName, const PSTR AuthMechanism, const BERVAL *cred, PLDAPControlA *ServerCtrls, PLDAPControlA *ClientCtrls, PBERVAL *ServerData);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_unbind(LDAP *ld);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_unbind_s(LDAP *ld);
// WINLDAPAPI LDAP *LDAPAPI Wldap32$ldap_openA(const PSTR  HostName, ULONG PortNumber);
WINLDAPAPI LDAP *LDAPAPI Wldap32$ldap_sslinitA(PSTR HostName, ULONG PortNumber, int secure);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_set_optionA(LDAP *ld, int option, const void *invalue);
WINLDAPAPI LDAPAPI ULONG Wldap32$ldap_simple_bind_s(LDAP *ld, const PSTR dn, const PSTR passwd);
WINLDAPAPI LDAPAPI ULONG Wldap32$LdapGetLastError();
