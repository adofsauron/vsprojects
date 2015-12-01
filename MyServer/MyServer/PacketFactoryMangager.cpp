#include "PacketFactoryMangager.h"

#include "CInitGame.h"
#include "CJoinGame.h"
#include "CDemage.h"
#include "CLoadOver.h"
#include "CPlayerDeath.h"
#include "CStatus.h"

PacketFactoryMangager::PacketFactoryMangager()
{
	m_packetFactory = new PacketFactory*[PACKET_C_GAME_OVER];
}

VOID PacketFactoryMangager::RegisterFactory(PacketFactory* factory)
{
	m_packetFactory[factory->GetPacketID()] = factory;
}

VOID PacketFactoryMangager::InitFactory()
{
	RegisterFactory(new CInitGameFactory	);
	RegisterFactory(new CJoinGameFactory	);
	RegisterFactory(new CDemageFactory		);
	RegisterFactory(new CLoadOverFactory	);
	RegisterFactory(new CPlayerDeathFactory	);
	RegisterFactory(new CStatusFactory		);
}

PacketFactory* PacketFactoryMangager::GetPacketFactory(UCHAR packetID)
{
	return m_packetFactory[packetID];
}