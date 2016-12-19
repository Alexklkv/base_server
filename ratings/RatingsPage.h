#pragma once

#include "BaseRatingRecord.h"
#include "NoCopy.h"

#include "server/Object.h"
#include "server/Writer.h"

#include <vector>

class RatingsPage : public server::Object
{
	friend class Ratings;

private:
	size_t places;

	std::vector<const BaseRatingRecord *> ratings;
	size_t count;

	void set(size_t place, const BaseRatingRecord *rating);

public:
	explicit RatingsPage(size_t places);

	const BaseRatingRecord* get(size_t index) const;

	void write(server::Writer *writer) const override;
};