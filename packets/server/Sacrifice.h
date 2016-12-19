#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class Sacrifice : public Packet
{
	SERVER_PACKET_HEADER(Sacrifice)

public:
	enum Status : uint8_t
	{
		SUCCESS = 0,
		FAILED
	};

	Sacrifice(Status status);
};

}