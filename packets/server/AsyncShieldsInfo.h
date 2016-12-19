#pragma once

#include "server/Packet.h"

class AsyncShields;

namespace server
{

class AsyncShieldsInfo : public Packet
{
	SERVER_PACKET_HEADER(AsyncShieldsInfo)

public:
	explicit AsyncShieldsInfo(const AsyncShields *async_shields);
};

}