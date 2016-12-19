#include "Request.h"

namespace server
{

namespace supports
{

SERVER_PACKET_SOURCE(Request)

Request::Request(Status status)
{
	this->add(static_cast<uint8_t>(status));
	this->write();
}

Request::Request(Status status, uint32_t assistant_id, const Supports::Key &key)
{
	this->add(static_cast<uint8_t>(status));
	this->add(assistant_id);
	this->add(static_cast<uint8_t>(key.type));
	this->add(key.id);

	this->write();
}

}

}