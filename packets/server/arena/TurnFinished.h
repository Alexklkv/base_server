#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class TurnFinished : public Packet
{
	SERVER_PACKET_HEADER(TurnFinished)

public:
	TurnFinished();
};

}

}