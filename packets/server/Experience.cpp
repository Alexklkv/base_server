#include "Experience.h"

#include "Enum.h"

namespace server
{

SERVER_PACKET_SOURCE(Experience)

Experience::Experience(AwardReason reason, uint32_t value)
{
	this->add(enum_unwrap(reason));
	this->add(value);
	this->write();

}

}