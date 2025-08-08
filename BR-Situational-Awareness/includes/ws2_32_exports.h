#include <winsock2.h>
#include <winsock.h>
#pragma once

DECLSPEC_IMPORT char * __stdcall Ws2_32$inet_ntoa(struct in_addr in);
__declspec(dllimport) __stdcall ULONG   Ws2_32$ntohl(u_long netlong);
__declspec(dllimport) __stdcall INT  	Ws2_32$inet_pton(INT Family, PCSTR pszAddrString, PVOID pAddrBuf);
__declspec(dllimport) __stdcall ULONG  	Ws2_32$htonl(u_long netlong);
__declspec(dllimport) __stdcall ULONG 	Ws2_32$inet_addr(const char *cp);
__declspec(dllimport) __stdcall ULONG 	Ws2_32$ntohl(ULONG netlong);
__declspec(dllimport) __stdcall int     Ws2_32$WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData);
__declspec(dllimport) __stdcall SOCKET 	Ws2_32$socket(int af, int type, int protocol);
__declspec(dllimport) __stdcall int     Ws2_32$WSAGetLastError();
__declspec(dllimport) __stdcall int 	Ws2_32$WSACleanup();
__declspec(dllimport) __stdcall int 	Ws2_32$setsockopt(SOCKET s,int level, int optname, const char *optval, int optlen);
__declspec(dllimport) __stdcall int 	Ws2_32$connect(SOCKET s, const struct sockaddr *name, int namelen);
__declspec(dllimport) __stdcall int 	Ws2_32$closesocket(SOCKET s);
__declspec(dllimport) __stdcall u_short Ws2_32$htons(u_short hostshort);
