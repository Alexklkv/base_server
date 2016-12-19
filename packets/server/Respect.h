#pragma once

#include "AwardReason.h"

#include "server/Packet.h"

namespace server
{

class Respect : public Packet
{
	SERVER_PACKET_HEADER(Respect)

public:
	Respect(AwardReason reason, uint32_t value);
};

}