#pragma once

#include "server/Group.h"
#include "server/Packet.h"

class Gifts;

namespace server
{

namespace gifts
{

class Storage : public Packet
{
	SERVER_PACKET_HEADER(Storage)

public:
	Storage(const ::Gifts *gifts);
};

}

}