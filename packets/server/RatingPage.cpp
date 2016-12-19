#include "RatingPage.h"

namespace server
{

SERVER_PACKET_SOURCE(RatingPage)

RatingPage::RatingPage(LegendsRatings::Category category, uint8_t type, uint32_t page_num, const ::RatingsPage *page)
{
	this->add(static_cast<uint8_t>(category));
	this->add(type);
	this->add(page_num);
	this->add(page);
	this->write();
}

}