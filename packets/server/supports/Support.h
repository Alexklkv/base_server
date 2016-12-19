#pragma once

#include "Supports.h"

#include "server/Packet.h"

namespace server
{

namespace supports
{

class Support : public Packet
{
	SERVER_PACKET_HEADER(Support)

public:
	Support(uint32_t assistant_id, const Supports::Key &key, uint32_t duration);
};

}

}