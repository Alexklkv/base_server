#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class BuyBonus : public Packet
{
	SERVER_PACKET_HEADER(BuyBonus)

public:

	BuyBonus(const server::Group &cards_group);
};

}