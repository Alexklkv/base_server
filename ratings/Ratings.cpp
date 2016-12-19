#include "Ratings.h"

#include "LegendsRatings.h"
#include "Log.h"

Ratings::Rating::Rating():
	records_count(0), pages_count(0)
{}

Ratings::Rating::~Rating()
{
	for (auto iter : this->records)
		delete iter;
}

Ratings::Ratings(const char *name, size_t page_places, size_t groups_count):
	page_places(page_places), groups_count(groups_count), name(name)
{
	this->ratings = new Rating[this->groups_count];
}

Ratings::~Ratings()
{
	delete [] this->ratings;
}

void Ratings::update()
{
	logger()->info("%s clearing", this->name);

	for (size_t i = 0; i < this->groups_count; i++)
	{
		this->ratings[i].records_count = 0;
		this->ratings[i].pages_count = 0;
	}

	this->clear();
	this->load();

	logger()->info("%s loaded", this->name);
}

size_t Ratings::size(size_t index) const
{
	if (index >= this->groups_count)
	{
		logger()->warning("Incorrect rating index %" PRIu64 " in %s", index, this->name);
		return 0;
	}

	return this->ratings[index].records_count;
}

void Ratings::reserve(size_t places, size_t index)
{
	if (index >= this->groups_count)
	{
		logger()->warning("Incorrect rating index %" PRIu64 " in %s", index, this->name);
		return;
	}

	Rating *rating = &ratings[index];

	for (auto iter = rating->records.grow_to_at_least(places + 1); iter != rating->records.end(); ++iter)
		*iter = this->create_record();

	rating->pages.grow_to_at_least(places / this->page_places + 1, RatingsPage(this->page_places));
}

BaseRatingRecord* Ratings::add_rating(size_t index)
{
	if (index >= this->groups_count)
	{
		logger()->warning("Incorrect rating index %" PRIu64 " in %s", index, this->name);
		return nullptr;
	}

	Rating *rating = &ratings[index];

	size_t place = rating->records_count;

	BaseRatingRecord *record = rating->records[place];

	rating->records_count++;

	size_t page = place / this->page_places;

	rating->pages[page].set(place, record);

	if (rating->pages_count < page + 1)
		rating->pages_count = page + 1;

	return record;
}

Ratings::records_t* Ratings::get_records(size_t index) const
{
	if (index >= this->groups_count)
	{
		logger()->warning("Incorrect rating index %" PRIu64 " in %s", index, this->name);
		return nullptr;
	}

	return &this->ratings[index].records;
}

const RatingsPage* Ratings::get_page(size_t page_num, size_t index) const
{
	if (index >= this->groups_count || page_num >= this->ratings[index].pages_count)
		return nullptr;

	return &(this->ratings[index].pages[page_num]);
}