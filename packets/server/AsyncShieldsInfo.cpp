#include "AsyncShieldsInfo.h"

#include <AsyncShields.h>

namespace server
{

SERVER_PACKET_SOURCE(AsyncShieldsInfo)

AsyncShieldsInfo::AsyncShieldsInfo(const AsyncShields *async_shields)
{
	this->add(async_shields);
	this->write();
}

}