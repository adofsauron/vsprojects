#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "stdafx.h"
#include "BaseType.h"
#include "SocketAPI.h"

class Socket
{
public:
	Socket();
	Socket(const CHAR* host, UINT port);
	virtual ~Socket();

public:
	BOOL	init();
	BOOL	create();
	VOID	close();

	BOOL	connect();
	BOOL	connect(const CHAR* host, UINT port);
	BOOL	reconnect(const CHAR* host, UINT port);

	UINT	send(const VOID* buf, UINT len, UINT flags=0);
	UINT	receive(VOID* buf, UINT len, UINT flags = 0);

	SOCKET	accept(struct sockaddr* addr, UINT* addrlen);
	BOOL	bind();
	BOOL	bind(UINT port);
	BOOL	listen(INT backlog);

public:
	BOOL	isNonBlocking()const;
	BOOL	setNonBlocking(BOOL on=TRUE);
	UINT	available()const;

	UINT	getPort()const;
	IP_t	getHostIP()const;
	SOCKET	getSOCKET()const;

public:
	SOCKET			m_SocketID;
	SOCKADDR_IN		m_SockAddr;
	CHAR			m_Host[IP_SIZE];
	UINT			m_Port;
};

#endif //_SOCKET_H_