#include "CardData.h"

#include "../../../CardHandler.h"
#include "../../../Summoner.h"
#include "server/Group.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(CardData)

CardData::CardData(const CardHandler *card, const Summoner *summoner)
{
	this->add(summoner->get_id());
	this->add(card);

	this->write();
}

}

}