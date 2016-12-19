#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class Messages : public Packet
{
	SERVER_PACKET_HEADER(Messages)

public:
	Messages(uint32_t interlocutor_id, const Group &messages);

};

}