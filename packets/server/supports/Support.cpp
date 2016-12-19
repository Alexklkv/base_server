#include "Support.h"

#include "server/Group.h"

namespace server
{

namespace supports
{

SERVER_PACKET_SOURCE(Support)

Support::Support(uint32_t assistant_id, const Supports::Key &key, uint32_t duration)
{
	this->add(assistant_id);
	this->add(static_cast<uint8_t>(key.type));
	this->add(key.id);
	this->add(duration);

	this->write();
}

}

}