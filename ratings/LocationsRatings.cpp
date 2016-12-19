#include "LocationsRatings.h"

#include "LocationsRatingRecord.h"
#include "RatingsParams.h"

#include "../Database.h"
#include "../LegendsServer.h"

LocationsRatings::LocationsRatings():
	LegendsRatings(LegendsRatings::RATINGS_LOCATIONS, 0, RatingsParams::LOCATION_RATINGS_NAME)
{}

LocationsRatings::~LocationsRatings()
{}

BaseRatingRecord* LocationsRatings::create_record() const
{
	return new LocationsRatingRecord;
}

void LocationsRatings::clear() const
{}

void LocationsRatings::load()
{
	database()->load_locations_ratings(this);
}