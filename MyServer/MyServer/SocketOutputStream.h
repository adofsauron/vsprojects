#ifndef _SOCKETOUTPUTSTREAM_H_
#define _SOCKETOUTPUTSTREAM_H_

#include "BaseType.h"
#include "Socket.h"

// 初始化的接收缓存长度
#define DEFAULTSOCKETINPUTBUFFERSIZE	64*1024
// 最大可以允许的缓存长度
#define	DISCONNECTSOCKETINPUTSIZE		94*1024

class Packet;

class SocketOutputStream
{
public:
	SocketOutputStream(Socket* socket,
		UINT BufferSize = DEFAULTSOCKETINPUTBUFFERSIZE,
		UINT MaxBufferSize = DISCONNECTSOCKETINPUTSIZE);
	virtual ~SocketOutputStream();

public:
	UINT		Write(const CHAR* buf, UINT len);
	INT			Flush();

	VOID		Initsize();
	BOOL		Resize(INT size);
	UINT		Capacity()const { return m_BufferLen; }
	UINT		Length()const;
	UINT		Size()const { return Length(); }
	BOOL		IsEmpty()const { return m_Head == m_Tail; }
	VOID		CleanUp();
	UINT		GetHead(){ return m_Head; }
	UINT		GetTail(){ return m_Tail; }
	UINT		GetBuffLen(){ return m_BufferLen; }
	CHAR*		GetBuff(){ return m_Buffer; }

private:
	Socket*		m_pSocket;
	CHAR*		m_Buffer;
	UINT		m_BufferLen;
	UINT		m_MaxBufferLen;
	UINT		m_Head;
	UINT		m_Tail;
};

#endif //_SOCKETOUTPUTSTREAM_H_