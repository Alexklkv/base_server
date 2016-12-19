#include "Arena.h"

#include "../Summoner.h"

namespace server
{

SERVER_PACKET_SOURCE(Arena)

Arena::Arena(uint8_t status, Summoner *summoner, Summoner *opponent)
{
	this->add(status);
	this->add(summoner);
	this->add(opponent);
	this->write();
}

Arena::Arena(uint8_t status, uint32_t first_player_id)
{
	this->add(static_cast<uint8_t>(status));
	this->add(first_player_id);
	this->write();
}

Arena::Arena(uint8_t status)
{
	this->add(static_cast<uint8_t>(status));
	this->write();
}

}