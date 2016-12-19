#pragma once

#include "LegendsRatings.h"

class LocationsRatings : public LegendsRatings
{
private:
	BaseRatingRecord* create_record() const override;

	void clear() const override;
	void load() override;

public:
	LocationsRatings();
	virtual ~LocationsRatings();
};