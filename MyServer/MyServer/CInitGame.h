#ifndef _CINITGAME_INCLUDE_H_
#define _CINITGAME_INCLUDE_H_

#include "Packet.h"
#include "BaseType.h"
#include "PacketDefined.h"

class CInitGame :public Packet
{
public:
	virtual BOOL Read(SocketInputStream&);
	virtual BOOL Write(SocketOutputStream&);
	virtual BOOL Execute();

public:
	virtual UCHAR	GetPacketID(){ return PACKET_C_INIT_GAME; }
	virtual USHORT	GetPacketSize(){ return sizeof(Packet_InitGame) + sizeof(CHAR); }

private:
	Packet_InitGame m_packet;
};


class CInitGameFactory :public PacketFactory
{
public:
	CInitGameFactory(){ cinitgame = new CInitGame; }
	~CInitGameFactory(){ delete cinitgame; };
	virtual UCHAR	GetPacketID(){ return PACKET_C_JOIN_GAME; }
	virtual Packet*	GetPacket(){ return cinitgame; }
private:
	CInitGame* cinitgame;
};

#endif //_CINITGAME_INCLUDE_H_