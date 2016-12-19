#include "LocationsInfo.h"

#include "../../Locations.h"

namespace server
{

SERVER_PACKET_SOURCE(LocationsInfo)

LocationsInfo::LocationsInfo(const Locations *locations)
{
	this->add(locations);
	this->write();
}

}