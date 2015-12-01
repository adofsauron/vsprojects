#ifndef _CLOADOVER_INCLUDE_H_
#define _CLOADOVER_INCLUDE_H_

#include "Packet.h"
#include "BaseType.h"
#include "PacketDefined.h"

class CLoadOver :public Packet
{
public:
	virtual BOOL Read(SocketInputStream&);
	virtual BOOL Write(SocketOutputStream&);
	virtual BOOL Execute();

public:
	virtual UCHAR	GetPacketID(){ return PACKET_C_LOAD_OVER; }
	virtual USHORT	GetPacketSize(){ return sizeof(Packet_LoadOver) + sizeof(CHAR); }

private:
	Packet_LoadOver m_packet;
};


class CLoadOverFactory :public PacketFactory
{
public:
	CLoadOverFactory(){ cloadover = new CLoadOver; }
	~CLoadOverFactory(){ delete cloadover; };
	virtual UCHAR	GetPacketID(){ return PACKET_C_LOAD_OVER; }
	virtual Packet*	GetPacket(){ return cloadover; }
private:
	CLoadOver* cloadover;
};

#endif //_CLOADOVER_INCLUDE_H_