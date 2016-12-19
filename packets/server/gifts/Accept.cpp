#include "Accept.h"

namespace server
{

namespace gifts
{

SERVER_PACKET_SOURCE(Accept)

Accept::Accept(Status status, uint32_t gift_id, Gifts::Type type, uint16_t bonus_id)
{
	this->add(static_cast<uint8_t>(status));
	this->add(gift_id);
	this->add(static_cast<uint8_t>(type));
	this->add(bonus_id);

	this->write();
}

Accept::Accept(Status status, uint32_t gift_id)
{
	this->add(static_cast<uint8_t>(status));
	this->add(gift_id);

	this->write();
}

}

}