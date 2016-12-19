#pragma once

#include "Ratings.h"
#include "Thread.h"

class LegendsRatings : public Ratings, public Thread
{
	friend class Database;
	friend class EloRewarder;

protected:
	virtual void clear() const override;

public:
	enum Category : uint8_t
	{
		RATINGS_COMMON,
		RATINGS_LOCATIONS,
		RATINGS_ELO,
		RATINGS_ELO_PREVIOUS,
		RATINGS_ELO_ASYNC,
		RATINGS_ELO_ASYNC_PREVIOUS,

		RATINGS_MAX_CATEGORY
	};

	const Category category;
	const uint8_t type;

	LegendsRatings(Category category, uint8_t type, const char *name);
	virtual ~LegendsRatings();

	virtual void on_timeout() override;
};