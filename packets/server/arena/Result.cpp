#include "Result.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(Result)

Result::Result(bool is_winner, uint16_t experience, uint32_t gold, uint16_t respect, uint16_t souls, const Group &items, const Group &cards)
{
	this->add(static_cast<uint8_t>(is_winner));
	this->add(experience);
	this->add(gold);
	this->add(respect);
	this->add(souls);
	this->add(&items);
	this->add(&cards);
	this->write();
}

}

}