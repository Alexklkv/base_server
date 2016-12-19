#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class InfoNet : public Packet
{
	SERVER_PACKET_HEADER(InfoNet)

public:
	InfoNet(const Group &players, uint32_t mask);
};

}