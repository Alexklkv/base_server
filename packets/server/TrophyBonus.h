#pragma once

#include "server/Packet.h"

#include "enums.h"

namespace server
{

class TrophyBonus : public Packet
{
	SERVER_PACKET_HEADER(TrophyBonus)

public:
	TrophyBonus(TrophyType trophy, uint32_t amount);

};

}