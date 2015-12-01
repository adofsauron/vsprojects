#include "Socket.h"
#include "SocketAPI.h"

#ifdef __LINUX__
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif

Socket::Socket()
{
	m_SocketID = INVALID_SOCKET;
	memset(&m_SockAddr, 0, sizeof(SOCKADDR));
	memset(m_Host, 0, IP_SIZE);
	m_Port = 0;
}

Socket::Socket(const CHAR* host, UINT port)
{
	memcpy(m_Host, host, IP_SIZE-1);
	m_Port = port;
	this->create();
}

Socket::~Socket()
{
	close();
}

BOOL Socket::init()
{
	int sock = m_SocketID;
	int bOptVal = 1;
	int bOptLen = sizeof(int);

	if ((setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (const CHAR*)&bOptVal, bOptLen) )== SOCKET_ERROR)
	{
		printf("adjust SO_KEEPLIVE faild.\n");
		return FALSE;
	}

	if ((setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const CHAR*)&bOptVal, bOptLen)) == SOCKET_ERROR)
	{
		printf("adjust TCP_NODELAY faild.\n");
		return FALSE;
	}

	if ((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const CHAR*)&bOptVal, bOptLen)) == SOCKET_ERROR)
	{
		printf("adjust SO_REUSEADDR faild.\n");
		return FALSE;
	}

	struct linger lgr;
	memset(&lgr, 0x00, sizeof(struct linger));
	lgr.l_onoff = 0;
	if ((setsockopt(sock, SOL_SOCKET, SO_LINGER, (const CHAR*)&lgr, sizeof(linger))) == SOCKET_ERROR)
	{
		printf("adjust SO_LINGER faild.\n");
		return FALSE;
	}

#ifdef __LINUX__
	bOptVal = 0;
	if ((setsockopt(sock, IPPROTO_TCP, TCP_CORK, (const CHAR*)&bOptVal, bOptLen)) == SOCKET_ERROR)
	{
		printf("adjust TCP_CORK faild.\n");
		return FALSE;
	}	
#endif

	this->setNonBlocking(TRUE);

	return TRUE;
}

BOOL Socket::create()
{
	m_SocketID = SocketAPI::socket_ex(AF_INET, SOCK_STREAM, 0);
	memset(&m_SockAddr, 0x00, sizeof(m_SockAddr));
	m_SockAddr.sin_family = AF_INET;

	if (m_SocketID != INVALID_SOCKET)
		return TRUE;
	else
		return FALSE;
}

BOOL Socket::reconnect(const CHAR* host, UINT port)
{
	this->close();
	memcpy(m_Host, host, IP_SIZE-1);
	m_Port = port;
	this->create();
	return this->connect();
}

VOID Socket::close()
{
	if (m_SocketID != INVALID_SOCKET)
	{
		_TRY
		{
			SocketAPI::closesocket_ex(m_SocketID);
		}
		_CATCH
		{
		}
	}

	m_SocketID = INVALID_SOCKET;
	memset(&m_SockAddr, 0x00, sizeof(m_SockAddr));
	memset(m_Host, 0, IP_SIZE);
	m_Port = 0;
}

BOOL Socket::connect()
{
	m_SockAddr.sin_addr.s_addr = inet_addr(m_Host);
	m_SockAddr.sin_port = htons(m_Port);
	BOOL result = SocketAPI::connect_ex(m_SocketID, (const struct sockaddr*)&m_SockAddr, sizeof(m_SockAddr)-1);
	if (result)
		return TRUE;
	else
		return FALSE;
}

BOOL Socket::connect(const CHAR* host, UINT port)
{
	memcpy(m_Host, host, IP_SIZE-1);
	m_Port = port;
	
	return this->connect();
}

UINT Socket::send(const VOID* buf, UINT len, UINT flags)
{
	return SocketAPI::send_ex(m_SocketID, buf, len, flags);
}

UINT Socket::receive( VOID* buf, UINT len, UINT flags)
{
	return SocketAPI::recv_ex(m_SocketID, buf, len, flags);
}

SOCKET Socket::accept(struct sockaddr* addr, UINT* addrlen)
{
	return SocketAPI::accept_ex(m_SocketID, addr, addrlen);
}

BOOL Socket::isNonBlocking()const
{
	return SocketAPI::getsocketnonblocking_ex(m_SocketID);
}

BOOL Socket::setNonBlocking(BOOL on)
{
	return SocketAPI::setsocketnonblocking_ex(m_SocketID, on);
}

UINT Socket::getPort()const
{
	return m_Port;
}

IP_t Socket::getHostIP()const
{
	return (IP_t)(m_SockAddr.sin_addr.s_addr);
}

SOCKET Socket::getSOCKET()const
{
	return m_SocketID;
}

BOOL Socket::bind()
{
	m_SockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	m_SockAddr.sin_port			= htons(m_Port);

	BOOL result = SocketAPI::bind_ex(m_SocketID, (const struct sockaddr*)&m_SockAddr, sizeof(m_SockAddr));

	if (result)
		return TRUE;
	else
		return FALSE;
}

BOOL Socket::bind(UINT port)
{
	m_Port = port;
	return this->bind();
}

BOOL Socket::listen(INT backlog)
{
	return SocketAPI::listen_ex(m_SocketID, backlog);
}

UINT Socket::available()const
{
	return SocketAPI::avaliablesocket_ex(m_SocketID);
}