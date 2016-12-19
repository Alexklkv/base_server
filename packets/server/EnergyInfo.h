#pragma once

#include "server/Group.h"
#include "server/Packet.h"

#include "../../resources/Energy.h"

namespace server
{

class EnergyInfo : public Packet
{
	SERVER_PACKET_HEADER(EnergyInfo)

public:
	EnergyInfo(Energy *energy);
};

}