#pragma once

#include "server/Packet.h"

class AsyncAttacks;

namespace server
{

class AsyncAttacksInfo : public Packet
{
	SERVER_PACKET_HEADER(AsyncAttacksInfo)

public:
	explicit AsyncAttacksInfo(const AsyncAttacks *offers);
};

}