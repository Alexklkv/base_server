#pragma once

#include "Supports.h"

#include "server/Packet.h"

namespace server
{

namespace supports
{

class Requests : public Packet
{
	SERVER_PACKET_HEADER(Requests)

public:
	Requests(uint32_t requester_id, const Supports::Key &key, uint32_t duration);
};

}

}