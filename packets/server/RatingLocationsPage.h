#pragma once

#include "../../ratings/RatingsPage.h"
#include "server/Packet.h"

namespace server
{

class RatingLocationsPage : public Packet
{
	SERVER_PACKET_HEADER(RatingLocationsPage)

public:
	RatingLocationsPage(uint32_t page_num, const ::RatingsPage *page);

};

}