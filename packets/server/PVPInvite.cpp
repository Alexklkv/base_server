#include "PVPInvite.h"

namespace server
{

SERVER_PACKET_SOURCE(PVPInvite)

PVPInvite::PVPInvite(uint32_t player_id)
{
	this->add(player_id);
	this->write();
}

}