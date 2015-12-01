#ifndef _PACKETFACTORYMANAGER_INCLUDE_H
#define _PACKETFACTORYMANAGER_INCLUDE_H

#include "BaseType.h"
#include "Packet.h"
#include "PacketDefined.h"

class PacketFactoryMangager
{
public:
	PacketFactoryMangager();
	~PacketFactoryMangager();

	VOID			InitFactory();
	VOID			RegisterFactory(PacketFactory* factory);
	PacketFactory*	GetPacketFactory(UCHAR packetID);

private:
	PacketFactory** m_packetFactory;
};

#endif //_PACKETFACTORYMANAGER_INCLUDE_H