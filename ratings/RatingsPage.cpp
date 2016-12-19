#include "RatingsPage.h"

#include "server/Group.h"

RatingsPage::RatingsPage(size_t places):
	places(places),
	count(0)
{
	this->ratings.resize(this->places);
}

const BaseRatingRecord* RatingsPage::get(size_t index) const
{
	return this->ratings[index];
}

void RatingsPage::set(size_t place, const BaseRatingRecord *rating)
{
	size_t pos = place % this->places;
	this->ratings[pos] = rating;
	this->count = pos + 1;
}

void RatingsPage::write(server::Writer *writer) const
{
	server::Group group;

	for (size_t i = 0; i < this->count; i++)
	{
		group.add(this->ratings[i]);
		group.next();
	}

	writer->add(&group);
}