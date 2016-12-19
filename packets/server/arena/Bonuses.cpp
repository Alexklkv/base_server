#include "Bonuses.h"

#include "server/Group.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(Bonuses)

Bonuses::Bonuses(server::Group &bonuses)
{
	this->add(&bonuses);
	this->write();
}

}

}