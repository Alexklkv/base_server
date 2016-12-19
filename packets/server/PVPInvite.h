#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class PVPInvite : public Packet
{
	SERVER_PACKET_HEADER(PVPInvite)

public:

	PVPInvite(uint32_t player_id);
};

}