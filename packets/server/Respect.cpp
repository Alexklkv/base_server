#include "Respect.h"

#include "Enum.h"

namespace server
{

SERVER_PACKET_SOURCE(Respect)

Respect::Respect(AwardReason reason, uint32_t value)
{
	this->add(enum_unwrap(reason));
	this->add(value);
	this->write();

}

}