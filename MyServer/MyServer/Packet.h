#ifndef _PACKET_INCLUDE_H
#define _PACKET_INCLUDE_H

#include "BaseType.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

class Packet
{
public:
	virtual BOOL Read(SocketInputStream&) = 0;
	virtual BOOL Read(SocketInputStream&, INT) { return TRUE; }
	virtual BOOL Write(SocketOutputStream&) = 0;
	virtual BOOL Execute()=0;

public:
	virtual UCHAR	GetPacketID() = 0;
	virtual USHORT	GetPacketSize() = 0;
};


class PacketFactory
{
public:
	virtual UCHAR	GetPacketID() = 0;
	virtual Packet*	GetPacket() = 0;
};
#endif //_PACKET_INCLUDE_H