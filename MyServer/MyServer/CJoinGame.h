#ifndef _CJOINGAME_INCLUDE_H_
#define _CJOINGAME_INCLUDE_H_

#include "Packet.h"
#include "BaseType.h"
#include "PacketDefined.h"

class CJoinGame:public Packet
{
public:
	virtual BOOL Read(SocketInputStream&);
	virtual BOOL Write(SocketOutputStream&);
	virtual BOOL Execute();

public:
	virtual UCHAR	GetPacketID(){ return PACKET_C_JOIN_GAME; }
	virtual USHORT	GetPacketSize(){ return sizeof(Packet_JoinGame) + sizeof(CHAR); }

private:
	Packet_JoinGame m_packet;
};


class CJoinGameFactory :public PacketFactory
{
public:
	CJoinGameFactory(){ cjoingame = new CJoinGame; }
	~CJoinGameFactory(){ delete cjoingame; };
	virtual UCHAR	GetPacketID(){ return PACKET_C_JOIN_GAME; }
	virtual Packet*	GetPacket(){return cjoingame;}
private:
	CJoinGame* cjoingame;
};

#endif //_CJOINGAME_INCLUDE_H_