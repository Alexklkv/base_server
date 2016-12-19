#include "Hello.h"

namespace server
{

SERVER_PACKET_SOURCE(Hello)

Hello::Hello()
{
	this->write();
}

}