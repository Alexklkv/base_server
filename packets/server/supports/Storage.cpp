#include "Storage.h"

#include "server/Group.h"

namespace server
{

namespace supports
{

SERVER_PACKET_SOURCE(Storage)

Storage::Storage(const Supports *supports)
{
	this->add(supports);

	this->write();
}

}

}