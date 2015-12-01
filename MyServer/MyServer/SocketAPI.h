#ifndef _SOCKETAPI_H_
#define _SOCKETAPI_H_

#include "BaseType.h"


#define _ESIZE 256

#if defined(__LINUX__)
typedef INT	SOCKET;
#define INVALID_SOCKET	-1
#define SOCKET_ERROR	-1
#endif

static const INT	SOCKET_ERROR_WOULDBLOCK = -100;

typedef	struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;
static const UINT szSOCKADDR_IN = sizeof(SOCKADDR_IN);

namespace SocketAPI
{
	SOCKET	socket_ex(INT domain, INT type, INT protocol);

	BOOL	bind_ex(SOCKET s, const struct sockaddr* name, UINT namelen);

	BOOL	connect_ex(SOCKET s, const struct sockaddr* name, UINT namelen);

	BOOL	listen_ex(SOCKET s, UINT backlog);

	SOCKET	accept_ex(SOCKET s, struct sockaddr* addr, UINT* addrlen);

	UINT	send_ex(SOCKET s, const VOID* buf, UINT len, UINT flags);

	UINT	sendto_ex(SOCKET s, const VOID* buf, INT len, UINT flags, const struct sockaddr* to, INT tolen);

	UINT	recv_ex(SOCKET s, VOID* buf, UINT len, UINT flags);

	UINT	recvfrom_ex(SOCKET s, VOID* buf, UINT len, UINT flags, const struct sockaddr* from, INT fromlen);

	BOOL	closesocket_ex(SOCKET s);

	BOOL	getsocketnonblocking_ex(SOCKET s);

	BOOL	setsocketnonblocking_ex(SOCKET s, BOOL on);

	INT		select_ex(INT maxfdpl, fd_set* readset, fd_set* writeset, fd_set* exceptset, struct timeval* timeout);

	UINT	avaliablesocket_ex(SOCKET s);
	
};

#pragma comment(lib,"ws2_32.lib")

#endif //_SOCKETAPI_H_