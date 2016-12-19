#pragma once

#include "NoCopy.h"
#include "RatingsPage.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdynamic-class-memaccess"
#include <concurrent_vector.h>
#pragma clang diagnostic pop

#include <cstddef>

class Ratings : private NoCopy
{
protected:
	typedef tbb::concurrent_vector<BaseRatingRecord*> records_t;

private:
	typedef tbb::concurrent_vector<RatingsPage> pages_t;

	struct Rating
	{
		pages_t pages;

		size_t records_count;
		size_t pages_count;

		records_t records;

		Rating();
		~Rating();
	};

	Rating *ratings;

	virtual BaseRatingRecord* create_record() const = 0;

	virtual void clear() const = 0;
	virtual void load() = 0;

protected:
	const size_t page_places;
	const size_t groups_count;

	const char *name;

	void reserve(size_t places, size_t index = 0);
	BaseRatingRecord* add_rating(size_t index = 0);

	records_t* get_records(size_t index = 0) const;

public:
	Ratings(const char *name, size_t page_places, size_t groups_count = 1);
	virtual ~Ratings();

	void update();

	size_t size(size_t index = 0) const;

	const RatingsPage* get_page(size_t page_num, size_t index = 0) const;
};