#pragma once

#include "AwardReason.h"

#include "server/Packet.h"

namespace server
{

class Balance : public Packet
{
	SERVER_PACKET_HEADER(Balance)

public:
	Balance(AwardReason reason, uint32_t gold, uint32_t souls);
};

}