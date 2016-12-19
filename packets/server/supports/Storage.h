#pragma once

#include "Supports.h"

#include "server/Packet.h"

namespace server
{

namespace supports
{

class Storage : public Packet
{
	SERVER_PACKET_HEADER(Storage)

public:
	Storage(const Supports *supports);
};

}

}