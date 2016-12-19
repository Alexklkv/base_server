#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class CardClick : public Packet
{
	SERVER_PACKET_HEADER(CardClick)

public:
	CardClick(uint32_t player_id, uint16_t card_id);
};

}

}