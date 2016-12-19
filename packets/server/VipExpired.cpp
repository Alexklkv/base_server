#include "VipExpired.h"

namespace server
{

SERVER_PACKET_SOURCE(VipExpired)

VipExpired::VipExpired()
{
	this->write();

}

}