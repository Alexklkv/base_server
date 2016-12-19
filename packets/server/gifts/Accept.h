#pragma once

#include "Gifts.h"

#include "server/Packet.h"

namespace server
{

namespace gifts
{

class Accept : public Packet
{
	SERVER_PACKET_HEADER(Accept)

public:
	enum Status
	{
		SUCCESS = 0,
		FAILED
	};

	Accept(Status status, uint32_t gift_id, Gifts::Type type, uint16_t bonus_id);
	Accept(Status status, uint32_t gift_id);
};

}

}