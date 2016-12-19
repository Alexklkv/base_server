#include "Requests.h"

#include "server/Group.h"

namespace server
{

namespace supports
{

SERVER_PACKET_SOURCE(Requests)

Requests::Requests(uint32_t requester_id, const Supports::Key &key, uint32_t duration)
{
	this->add(requester_id);
	this->add(static_cast<uint8_t>(key.type));
	this->add(key.id);
	this->add(duration);

	this->write();
}

}

}