#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class Result : public Packet
{
	SERVER_PACKET_HEADER(Result)

public:
	Result(bool is_winner, uint16_t experience, uint32_t gold, uint16_t respect, uint16_t souls, const Group &items, const Group &cards);
};

}

}