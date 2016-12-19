#pragma once

#include "../../ratings/LegendsRatings.h"
#include "server/Packet.h"

namespace server
{

class RatingPage : public Packet
{
	SERVER_PACKET_HEADER(RatingPage)

public:
	RatingPage(LegendsRatings::Category category, uint8_t type, uint32_t page_num, const ::RatingsPage *page);
};

}