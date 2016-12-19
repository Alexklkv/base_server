#include "EnergyInfo.h"

namespace server
{

SERVER_PACKET_SOURCE(EnergyInfo)

EnergyInfo::EnergyInfo(Energy *energy)
{
	this->add(energy);
	this->write();
}

}