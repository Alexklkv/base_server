#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class Bonuses : public Packet
{
	SERVER_PACKET_HEADER(Bonuses)

public:
	Bonuses(server::Group &bonuses);
};

}

}