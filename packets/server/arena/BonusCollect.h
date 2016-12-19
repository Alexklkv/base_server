#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class BonusCollect : public Packet
{
	SERVER_PACKET_HEADER(BonusCollect)

public:
	BonusCollect(uint8_t bonus_id);
	BonusCollect(uint8_t bonus_id, uint16_t card_id, uint8_t amount);
};

}

}