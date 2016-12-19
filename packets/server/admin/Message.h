#pragma once

#include "server/Packet.h"

namespace server
{

namespace admin
{

class Message : public Packet
{
	SERVER_PACKET_HEADER(Message)

public:
	explicit Message(const char *message);
};

}

}