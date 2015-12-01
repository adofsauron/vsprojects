#include "stdafx.h"
#include "SocketInputStream.h"
#include "Packet.h"
#include "PacketDefined.h"

SocketInputStream::SocketInputStream(Socket* sock, UINT BufferSize, UINT MaxBufferSize )
{
	m_pSocket		= sock;
	m_BufferLen	= BufferSize;
	m_MaxBufferLen	= MaxBufferSize;
	m_Head			= 0;
	m_Tail			= 0;
	m_Buffer		= new CHAR[m_BufferLen];
	memset(m_Buffer, 0x00, m_BufferLen);
}

SocketInputStream::~SocketInputStream()
{
	if (m_Buffer)
		delete[] m_Buffer;
}

UINT SocketInputStream::Length() const
{
	if (m_Head < m_Tail)
		return m_Tail - m_Head;
	else if (m_Head > m_Tail)
		return m_BufferLen - m_Head + m_Tail;
	else
		return 0;
}

UINT SocketInputStream::Read(CHAR* buf, UINT len)
{
	if ((len == 0) || (len > Length()))
		return 0;

	if (m_Head < m_Tail)
	{
		memcpy(buf, &m_Buffer[m_Head], len);
	}
	else
	{
		UINT rightLen = m_BufferLen - m_Head;
		if (len <= rightLen)
		{
			memcpy(buf, &m_Buffer[m_Head], len);
			memcpy(&buf[rightLen], m_Buffer, len-rightLen);
		}
	}
		
	m_Head = (m_Head + len) % m_BufferLen;
	
	return len;
}

BOOL SocketInputStream::ReadPacket(Packet* pPacket, INT readLen)
{
	BOOL ret;
	ret = this->Skip(HEAD_LEN);
	if (!ret)
		return FALSE;

	if (readLen != 0)
		return pPacket->Read(*this, readLen);

	return pPacket->Read(*this);
}

BOOL SocketInputStream::Peek(CHAR* buf, UINT len)
{
	if ((len == 0) || (len > Length()))
		return FALSE;

	if (m_Head < m_Tail)
	{
		memcpy(buf, &m_Buffer[m_Head], len);
	}
	else
	{
		UINT rightLen = m_BufferLen - m_Head;
		if (len <= rightLen)
		{
			memcpy(buf, &m_Buffer[m_Head], len);
			memcpy(&buf[rightLen], m_Buffer, len - rightLen);
		}
	}

	return TRUE;
}

BOOL SocketInputStream::Skip(UINT len)
{
	if ((len == 0) || (len > Length()))
		return FALSE;

	m_Head = (m_Head + len) % m_BufferLen;
	return TRUE;
}

VOID SocketInputStream::Initsize()
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

UINT SocketInputStream::Fill()
{
	INT nFilled		= 0;
	INT	nRecived	= 0;
	INT	nFree		= 0;

	if (m_Head <= m_Tail)
	{
		if (m_Head == 0)
		{
			nRecived = 0;
			nFree = m_BufferLen - m_Tail - 1;
			if (nFree != 0)
			{
				nRecived = m_pSocket->receive(&m_Buffer[m_Tail], nFree);
				if (!nRecived)
				{
					printf("receive error!\n");
					return -1;
				}

				m_Tail	+= nRecived;
				nFilled += nRecived;
			}

			if (nRecived == nFree)
			{
				UINT avaliable = m_pSocket->available();
				if (avaliable)
				{
					if ((m_BufferLen + avaliable + 1) > m_MaxBufferLen)
					{
						this->Initsize();
						return -1;
					}

					if (!Resize(avaliable + 1))
						return 0;

					nRecived = m_pSocket->receive(&m_Buffer[m_Tail], avaliable);
					if (!nRecived)
					{
						printf("receive error!\n");
						return -1;
					}

					m_Tail += nRecived;
					nFilled += nRecived;

				}
			}
		}
		else
		{
			nRecived = 0;
			nFree = m_BufferLen - m_Tail - 1;
			nRecived = m_pSocket->receive(&m_Buffer[m_Tail], nFree);
			if (!nRecived)
			{
				printf("receive error!\n");
				return -1;
			}
			m_Tail = (m_Tail+nRecived) % m_BufferLen;
			nFilled += nRecived;

			if (nRecived == nFree)
			{
				nRecived = 0;
				nFree = m_Head - 1;
				if (nFree != 0)
				{
					nRecived = m_pSocket->receive(&m_Buffer[0], nFree);
					if (!nRecived)
					{
						printf("receive error!\n");
						return -1;
					}

					m_Tail += nRecived;
					nFilled += nRecived;

				}

				if (nRecived == nFree)
				{
					UINT avaliable = m_pSocket->available();
					if (avaliable)
					{
						if ((m_BufferLen + avaliable + 1) > m_MaxBufferLen)
						{
							this->Initsize();
							return -1;
						}

						if (!Resize(avaliable + 1))
							return 0;

						nRecived = m_pSocket->receive(&m_Buffer[m_Tail], avaliable);
						if (!nRecived)
						{
							printf("receive error!\n");
							return -1;
						}

						m_Tail += nRecived;
						nFilled += nRecived;

					}
				}

			}
		}
		
	}
	else
	{
		nRecived = 0;
		nFree = m_BufferLen - m_Tail - 1;
		nRecived = m_pSocket->receive(&m_Buffer[m_Tail], nFree);
		if (!nRecived)
		{
			printf("receive error!\n");
			return -1;
		}
		m_Tail	+=nRecived;
		nFilled += nRecived;

		if (nRecived == nFree)
		{
			UINT avaliable = m_pSocket->available();
			if (avaliable)
			{
				if ((m_BufferLen + avaliable + 1) > m_MaxBufferLen)
				{
					this->Initsize();
					return -1;
				}

				if (!Resize(avaliable + 1))
					return 0;

				nRecived = m_pSocket->receive(&m_Buffer[m_Tail], avaliable);
				if (!nRecived)
				{
					printf("receive error!\n");
					return -1;
				}

				m_Tail += nRecived;
				nFilled += nRecived;

			}
		}
	}

	return nFilled;
	
}

BOOL SocketInputStream::Resize(INT size)
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
		memcpy(&newBuffer[m_BufferLen-m_Head], m_Buffer, m_Tail);
	}

	delete[] m_Buffer;

	m_Buffer = newBuffer;
	m_BufferLen = newBufferLen;
	m_Head = 0;
	m_Tail = len;

	return TRUE;
}

VOID SocketInputStream::CleanUp()
{
	m_Head = 0;
	m_Tail = 0;
}

