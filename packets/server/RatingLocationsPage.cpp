#include "RatingLocationsPage.h"

namespace server
{

SERVER_PACKET_SOURCE(RatingLocationsPage)

RatingLocationsPage::RatingLocationsPage(uint32_t page_num, const ::RatingsPage *page)
{
	this->add(page_num);
	this->add(page);

	this->write();
}

}