#include "OffersInfo.h"

#include <Offers.h>

namespace server
{

SERVER_PACKET_SOURCE(OffersInfo)

OffersInfo::OffersInfo(const Offers *offers)
{
	this->add(offers);
	this->write();
}

}