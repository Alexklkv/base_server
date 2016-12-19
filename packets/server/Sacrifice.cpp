#include "Sacrifice.h"

namespace server
{

SERVER_PACKET_SOURCE(Sacrifice)

Sacrifice::Sacrifice(Status status)
{
	this->add(static_cast<uint8_t>(status));
	this->write();
}

}