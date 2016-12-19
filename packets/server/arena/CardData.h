#pragma once

#include "server/Packet.h"

class CardHandler;
class Summoner;

namespace server
{

namespace arena
{

class CardData : public Packet
{
	SERVER_PACKET_HEADER(CardData)

public:
	CardData(const CardHandler *card, const Summoner *summoner);
};

}

}