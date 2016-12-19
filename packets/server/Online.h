#pragma once

#include "server/Packet.h"

namespace server
{

class Online : public Packet
{
	SERVER_PACKET_HEADER(Online)

public:
	Online(uint32_t value);
};

}