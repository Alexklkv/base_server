#pragma once

#include "server/Packet.h"

namespace server
{

namespace arena
{

class Chat : public Packet
{
	SERVER_PACKET_HEADER(Chat)

public:
	Chat(const char *message);
};

}

}