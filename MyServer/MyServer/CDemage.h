#ifndef _CDEMAGE_INCLUDE_H_
#define _CDEMAGE_INCLUDE_H_

#include "Packet.h"
#include "BaseType.h"
#include "PacketDefined.h"

class CDemage :public Packet
{
public:
	virtual BOOL Read(SocketInputStream&);
	virtual BOOL Write(SocketOutputStream&);
	virtual BOOL Execute();

public:
	virtual UCHAR	GetPacketID(){ return PACKET_C_DEMAGE; }
	virtual USHORT	GetPacketSize(){ return sizeof(Packet_Demage) + sizeof(CHAR); }

private:
	Packet_Demage m_packet;
};


class CDemageFactory :public PacketFactory
{
public:
	CDemageFactory(){ cdemage = new CDemage; }
	~CDemageFactory(){ delete cdemage; };
	virtual UCHAR	GetPacketID(){ return PACKET_C_DEMAGE; }
	virtual Packet*	GetPacket(){ return cdemage; }
private:
	CDemage* cdemage;
};

#endif //_CDEMAGE_INCLUDE_H_