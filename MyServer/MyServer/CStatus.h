#ifndef _CSTATUS_INCLUDE_H_
#define _CSTATUS_INCLUDE_H_

#include "Packet.h"
#include "BaseType.h"
#include "PacketDefined.h"

class CStatus :public Packet
{
public:
	virtual BOOL  Read(SocketInputStream&);
	virtual BOOL Write(SocketOutputStream&);
	virtual BOOL Execute();

public:
	virtual UCHAR	GetPacketID(){ return PACKET_C_STATUS; }
	virtual USHORT	GetPacketSize(){ return sizeof(Packet_Status) + sizeof(CHAR); }

private:
	Packet_Status m_packet;
};


class CStatusFactory :public PacketFactory
{
public:
	CStatusFactory(){ cstatus = new CStatus; }
	~CStatusFactory(){ delete cstatus; };
	virtual UCHAR	GetPacketID(){ return PACKET_C_STATUS; }
	virtual Packet*	GetPacket(){ return cstatus; }
private:
	CStatus* cstatus;
};

#endif //_CSTATUS_INCLUDE_H_