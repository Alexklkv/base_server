#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class AsyncAward : public Packet
{
	SERVER_PACKET_HEADER(AsyncAward)

public:
	enum Type : uint8_t
	{
		CHOOSE_HAPPY = 0,
		CHOOSE_ANY,
		RESULT
	};

	AsyncAward(uint16_t card_type, uint8_t card_level);
};

}