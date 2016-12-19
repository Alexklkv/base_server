#include "Info.h"

namespace server
{

SERVER_PACKET_SOURCE(Info)

Info::Info(const Group &players, uint32_t mask)
{
	this->add(&players, true);
	this->add(mask);

	this->write();
}

}