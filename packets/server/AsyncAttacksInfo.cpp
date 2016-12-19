#include "AsyncAttacksInfo.h"

#include <AsyncAttacks.h>

namespace server
{

SERVER_PACKET_SOURCE(AsyncAttacksInfo)

AsyncAttacksInfo::AsyncAttacksInfo(const AsyncAttacks *async_attacks)
{
	this->add(async_attacks);
	this->write();
}

}