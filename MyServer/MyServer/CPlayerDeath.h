#ifndef _CPlayerDeath_INCLUDE_H_
#define _CPlayerDeath_INCLUDE_H_

#include "Packet.h"
#include "BaseType.h"
#include "PacketDefined.h"

class CPlayerDeath :public Packet
{
public:
	virtual BOOL Read(SocketInputStream&);
	virtual BOOL Write(SocketOutputStream&);
	virtual BOOL Execute();

public:
	virtual UCHAR	GetPacketID(){ return PACKET_C_JOIN_GAME; }
	virtual USHORT	GetPacketSize(){ return sizeof(Packet_PlayerDeath) + sizeof(CHAR); }

private:
	Packet_PlayerDeath m_packet;
};


class CPlayerDeathFactory :public PacketFactory
{
public:
	CPlayerDeathFactory(){ cplayerdeath = new CPlayerDeath; }
	~CPlayerDeathFactory(){ delete cplayerdeath; };
	virtual UCHAR	GetPacketID(){ return PACKET_C_JOIN_GAME; }
	virtual Packet*	GetPacket(){ return cplayerdeath; }
private:
	CPlayerDeath* cplayerdeath;
};

#endif //_CPlayerDeath_INCLUDE_H_