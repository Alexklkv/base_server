#include "CardClick.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(CardClick)

CardClick::CardClick(uint32_t player_id, uint16_t card_id)
{
	this->add(player_id);
	this->add(card_id);
	this->write();
}

}

}