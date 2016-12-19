#include "BuyBonus.h"

namespace server
{

SERVER_PACKET_SOURCE(BuyBonus)

BuyBonus::BuyBonus(const server::Group &cards_group)
{
	this->add(&cards_group);
	this->write();
}

}