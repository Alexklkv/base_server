#pragma once

#include "server/Packet.h"

class Offers;

namespace server
{

class OffersInfo : public Packet
{
	SERVER_PACKET_HEADER(OffersInfo)

public:
	explicit OffersInfo(const Offers *offers);
};

}