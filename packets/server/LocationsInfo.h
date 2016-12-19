#pragma once

#include "server/Packet.h"

#include "enums.h"

class Locations;

namespace server
{

class LocationsInfo : public Packet
{
	SERVER_PACKET_HEADER(LocationsInfo)

public:
	LocationsInfo(const Locations *locations);

};

}