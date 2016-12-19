#include "Balance.h"

#include "Enum.h"

namespace server
{

SERVER_PACKET_SOURCE(Balance)

Balance::Balance(AwardReason reason, uint32_t gold, uint32_t souls)
{
	this->add(enum_unwrap(reason));
	this->add(gold);
	this->add(souls);
	this->write();

}

}