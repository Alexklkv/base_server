#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class NextRound : public Packet
{
	SERVER_PACKET_HEADER(NextRound)

public:
	NextRound();
};

}

}