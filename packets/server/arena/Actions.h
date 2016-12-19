#pragma once

#include "server/Packet.h"

class RoundActionsLog;

namespace server
{

namespace arena
{

class Actions : public Packet
{
	SERVER_PACKET_HEADER(Actions)

public:
	Actions(const RoundActionsLog *actions);
};

}

}