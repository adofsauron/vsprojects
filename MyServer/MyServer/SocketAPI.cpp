#include "stdafx.h"
#include "SocketAPI.h"


#ifdef __LINUX__
extern INT errno;
#endif

CHAR Error[_ESIZE];


SOCKET	SocketAPI::socket_ex(INT domain, INT type, INT protocol)
{
	SOCKET s = ::socket(domain, type, protocol);

	if (s == INVALID_SOCKET)
	{
#ifdef __LINUX__
		printf("socket[%d] error in LINUX\n", s);
#elif __WIN__
		printf("socket[%d] error in WIN\n", s);
#endif
	}

	return s;
}

BOOL SocketAPI::bind_ex(SOCKET s, const struct sockaddr* name, UINT namelen)
{
	if (bind(s, name, namelen) == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("bind[%d] error in LINUX\n", s);
#elif __WIN__
		printf("bind[%d] error in WIN\n", s);
#endif
		return FALSE;
	}

	return TRUE;
}

BOOL SocketAPI::connect_ex(SOCKET s, const struct sockaddr* addr, UINT addrlen)
{
	if (connect(s, addr, addrlen) == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("connect[%d] error in LINUX\n", s);
#elif __WIN__
		printf("connect[%d] error in WIN\n", s);
#endif

		return FALSE;
	}

	return TRUE;
}

BOOL SocketAPI::listen_ex(SOCKET s, UINT backlog)
{
	if (listen(s, backlog) == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("listen[%d] error in LINUX\n", s);
#elif __WIN__
		printf("listen[%d] error in WIN\n", s);
#endif

		return FALSE;
	}

	return TRUE;
}

SOCKET SocketAPI::accept_ex(SOCKET s, struct sockaddr* addr, UINT* addrlen)
{
	SOCKET client;
#ifdef __LINUX__
	client = accept(s, addr, addrlen);
#elif __WIN__
	client = accept(s, addr, (INT*)addrlen);
#endif

	if (client == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("listen[%d] error in LINUX\n", s);
		#elif __WIN__
		printf("listen[%d] error in WIN\n", s);
#endif

		return SOCKET_ERROR;
	}

	return client;
}

UINT SocketAPI::send_ex(SOCKET s, const VOID* buf, UINT len, UINT flags)
{
	INT nSent;
#ifdef __LINUX__
	nSent = send(s, buf, len, flags);
#elif  __WIN__
	nSent = send(s, (const CHAR*)buf, len, flags);
#endif

	if (nSent == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("send[%d] error in LINUX\n", s);
#elif __WIN__
		printf("send[%d] error in WIN\n", s);
#endif

		return SOCKET_ERROR;
	}

	return nSent;
}

UINT SocketAPI::sendto_ex(SOCKET s, const VOID* buf, INT len, UINT flags, const struct sockaddr* to, INT tolen)
{
	INT nSent;
#ifdef __LINUX__
	nSent = sendto(s, buf, len, flags, to, tolen);
#elif  __WIN__
	nSent = sendto(s, (const CHAR*)buf, len, flags, to, tolen);
#endif

	if (nSent == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("send[%d] error in LINUX\n", s);
		#elif __WIN__
		printf("send[%d] error in WIN\n", s);
#endif

		return SOCKET_ERROR;
	}

	return nSent;
}

UINT SocketAPI::recv_ex(SOCKET s, VOID* buf, UINT len, UINT flags)
{
	INT nRecv;
#ifdef __LINUX__
	nRecv = recv(s, buf, len, flags);
#elif  __WIN__
	nRecv = recv(s, (CHAR*)buf, len, flags);
#endif

	if (nRecv == SOCKET_ERROR)
	{
#ifdef __LINUX__
		printf("recv[%d] error in LINUX", s);
#elif __WIN__
		printf("recv[%d] error in WIN\n", s);
#endif

		return SOCKET_ERROR;
	}

	return nRecv;
}

UINT SocketAPI::recvfrom_ex(SOCKET s, VOID* buf, UINT len, UINT flags, const struct sockaddr* from, INT fromlen)
{
	return NULL;
}

BOOL SocketAPI::closesocket_ex(SOCKET s)
{
#ifdef __LINUX__
	::close(s);
#elif  __WIN__
	if (closesocket(s) == SOCKET_ERROR)
	{
		printf("close socket[%d] error\n", s);
		return FALSE;
	}
#endif

	return TRUE;
}

BOOL SocketAPI::getsocketnonblocking_ex(SOCKET s)
{
#ifdef __LINUX__
	INT flags = fcntl(s, F_GETFL, 0);
	return flags | O_NONBLOCK;
#elif  __WIN__
	return FALSE;
#endif
}

BOOL SocketAPI::setsocketnonblocking_ex(SOCKET s, BOOL on)
{
#ifdef __LINUX__
	INT flags = fcntl(s, F_GETFL, 0);
	if (on)
	{
		flags |= O_NONBLOCK;
	}
	else
	{
		flags &= ~O_NONBLOCK;
	}

	return TRUE;
#elif __WIN__
	ULONG argp = (on == TRUE) ? 1 : 0;
	return ioctlsocket(s, FIONBIO, &argp);
#endif
}

INT	 SocketAPI::select_ex(INT maxfdpl, fd_set* readset, fd_set* writeset, fd_set* exceptset, struct timeval* timeout)
{
	INT result;
	result = select(maxfdpl, readset, writeset, exceptset, timeout);

#ifdef __LINUX__

#elif	__WIN__
	printf("select error in WIN\n");
#endif

	return result;
}

UINT SocketAPI::avaliablesocket_ex(SOCKET s)
{
#ifdef __LINUX__
	UINT arg=0;
	ioctl(s, FIONREAD, &arg);
	return arg;
#elif __WIN__
	ULONG arg = 0;
	ioctlsocket(s, FIONREAD, &arg);
	return arg;
#endif
}