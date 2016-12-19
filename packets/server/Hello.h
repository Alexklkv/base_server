#pragma once

#include "server/Packet.h"

namespace server
{

class Hello : public Packet
{
	SERVER_PACKET_HEADER(Hello)

public:
	Hello();
};

}