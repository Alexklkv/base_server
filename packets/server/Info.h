#pragma once

#include "server/Group.h"
#include "server/Packet.h"

class Player;

namespace server
{

class Info : public Packet
{
	SERVER_PACKET_HEADER(Info)

public:
	Info(const Group &players, uint32_t mask);
};

}