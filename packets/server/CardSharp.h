#pragma once

#include "ICard.h"

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class CardSharp : public Packet
{
	SERVER_PACKET_HEADER(CardSharp)

public:
	CardSharp(bool is_sharped);
};

}