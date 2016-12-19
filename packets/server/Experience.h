#pragma once

#include "AwardReason.h"

#include "server/Packet.h"

namespace server
{

class Experience : public Packet
{
	SERVER_PACKET_HEADER(Experience)

public:
	Experience(AwardReason reason, uint32_t value);
};

}