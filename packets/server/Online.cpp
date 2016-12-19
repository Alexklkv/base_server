#include "Online.h"

namespace server
{

SERVER_PACKET_SOURCE(Online)

Online::Online(uint32_t value)
{
	this->add(value);
	this->write();
}

}