#pragma once

#include "server/Packet.h"
#include "enums.h"

namespace server
{

class FlagState : public Packet
{
	SERVER_PACKET_HEADER(FlagState)

public:
	FlagState(FlagType type, uint16_t flag);
};

}