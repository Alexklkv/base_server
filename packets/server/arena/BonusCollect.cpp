#include "BonusCollect.h"

#include "server/Group.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(BonusCollect)

BonusCollect::BonusCollect(uint8_t bonus_id)
{
	this->add(bonus_id);
	this->write();
}

BonusCollect::BonusCollect(uint8_t bonus_id, uint16_t card_id, uint8_t amount)
{
	this->add(bonus_id);
	this->add(card_id);
	this->add(amount);
	this->write();
}

}

}