#pragma once

#include "server/Packet.h"

#include "enums.h"

class Cards;

namespace server
{

class CardsRequest : public Packet
{
	SERVER_PACKET_HEADER(CardsRequest)

public:
	CardsRequest(CardRequestReason reason, Cards *cards);
};

}