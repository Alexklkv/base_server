#pragma once

#include "server/Packet.h"

namespace server
{

class VipExpired : public Packet
{
	SERVER_PACKET_HEADER(VipExpired)

public:
	VipExpired();
};

}