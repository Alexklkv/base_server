#include "InfoNet.h"

namespace server
{

SERVER_PACKET_SOURCE(InfoNet)

InfoNet::InfoNet(const Group &players, uint32_t mask)
{
	this->add(&players, true);
	this->add(mask);

	this->write();
}

}