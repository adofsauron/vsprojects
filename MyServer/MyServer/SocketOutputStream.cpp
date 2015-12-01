#include "stdafx.h"
#include "SocketOutputStream.h"
#include "Packet.h"
#include "PacketDefined.h"

SocketOutputStream::SocketOutputStream(Socket* sock, UINT BufferSize, UINT MaxBufferSize)
{
	m_pSocket = sock;
	m_BufferLen = BufferSize;
	m_MaxBufferLen = MaxBufferSize;
	m_Head = 0;
	m_Tail = 0;
	m_Buffer = new CHAR[m_BufferLen];
	memset(m_Buffer, 0x00, m_BufferLen);
}

SocketOutputStream::~SocketOutputStream()
{
	if (m_Buffer)
		delete[] m_Buffer;
}

UINT SocketOutputStream::Length() const
{
	if (m_Head < m_Tail)
		return m_Tail - m_Head;
	else if (m_Head > m_Tail)
		return m_BufferLen - m_Head + m_Tail;
	else
		return 0;
}

UINT SocketOutputStream::Write(const CHAR* buf, UINT len)
{
	UINT nFree = ((m_Head <= m_Tail) ? (m_BufferLen - m_Tail + m_Head - 1) : (m_Head - m_Tail - 1));

	if (len >= nFree)
	{
		if (!Resize(len - nFree + 1))
		{
			printf("Resize false\n");
			return 0;
		}
	}

	if (m_Head <= m_Tail)
	{
		if (m_Head == 0)
		{
			nFree = m_BufferLen - m_Tail - 1;
			memcpy(&m_Buffer[m_Tail], buf, len);
		}
		else
		{
			nFree = m_BufferLen - m_Tail;
			if (len <= nFree)
			{
				memcpy(&m_Buffer[m_Tail], buf, len);
			}
			else
			{
				memcpy(&m_Buffer[m_Tail], buf, nFree);
				memcpy(&m_Buffer, &buf[nFree], len - nFree);
			}
		}
	}
	else
	{
		memcpy(&m_Buffer[m_Tail], buf, len);
	}

	m_Tail = (m_Tail + len) % m_BufferLen;
	return len;
}


VOID SocketOutputStream::Initsize()
{
	m_Head = 0;
	m_Tail = 0;

	if (m_Buffer)
		delete[] m_Buffer;

	m_Buffer = new CHAR[DEFAULTSOCKETINPUTBUFFERSIZE];
	assert(m_Buffer);
	m_BufferLen = DEFAULTSOCKETINPUTBUFFERSIZE;
	memset(m_Buffer, 0, m_BufferLen);
}

INT SocketOutputStream::Flush()
{
	INT nFlushed	= 0;
	INT nSent		= 0;
	INT nLeft		= 0;

	if (m_BufferLen > m_MaxBufferLen)
	{
		Initsize();
		return -1;
	}

#ifdef __WIN__
	UINT flag = MSG_DONTROUTE;
#else
	UINT flag = MSG_NOSIGNAL;
#endif

	try
	{
		if (m_Head < m_Tail)
		{
			nLeft = m_Tail - m_Head;
			while (nLeft > 0)
			{
				nSent = m_pSocket->send(&m_Buffer[m_Head],nLeft, flag);
				if (!nSent)
					return -1;

				nFlushed += nSent;
				nLeft	 -= nSent;
				m_Head 	 += nSent;
			}
		}
		else if (m_Head > m_Tail)
		{
			nLeft = m_BufferLen - m_Head;
			while (nLeft > 0)
			{
				nSent = m_pSocket->send(&m_Buffer[m_Head], nLeft, flag);
				if (!nSent)
					return -1;

				nFlushed += nSent;
				nLeft	 -= nSent;
				m_Head	 += nSent;
			}
		}

		m_Head = 0;
		nLeft = m_Tail;
		while (nLeft > 0)
		{
			nSent = m_pSocket->send(&m_Buffer[m_Head], nLeft, flag);
			if (!nSent)
				return -1;

			nFlushed += nSent;
			nLeft	 -= nSent;
			m_Head	 += nSent;
		}
	}
	catch(...)
	{
		if (nSent > 0)
		{
			m_Head += nSent;
		}
	}

	m_Head = m_Tail = 0;
	
	return nFlushed;
}

BOOL SocketOutputStream::Resize(INT size)
{
	INT mbl = (int)m_BufferLen >> 1;
	size = size > mbl ? size : mbl;
	INT	newBufferLen = m_BufferLen + size;
	INT len = Length();

	if (size < 0)
	{
		if ((newBufferLen < 0) || (newBufferLen < len))
			return FALSE;
	}

	CHAR* newBuffer = new CHAR[newBufferLen];

	if (m_Head < m_Tail)
	{
		memcpy(newBuffer, &m_Buffer[m_Head], m_Tail - m_Head);
	}
	else if (m_Head > m_Tail)
	{
		memcpy(newBuffer, &m_Buffer[m_Head], m_BufferLen - m_Head);
		memcpy(&newBuffer[m_BufferLen - m_Head], m_Buffer, m_Tail);
	}

	delete[] m_Buffer;

	m_Buffer = newBuffer;
	m_BufferLen = newBufferLen;
	m_Head = 0;
	m_Tail = len;

	return TRUE;
}

VOID SocketOutputStream::CleanUp()
{
	m_Head = 0;
	m_Tail = 0;
}