#include "CommonRatings.h"

#include "../Database.h"
#include "../LegendsServer.h"
#include "../Player.h"

CommonRatings::CommonRatings(Type type, const char *name):
	LegendsRatings(LegendsRatings::RATINGS_COMMON, type, name)
{}

CommonRatings::~CommonRatings()
{}

BaseRatingRecord* CommonRatings::create_record() const
{
	return new BaseRatingRecord;
}

void CommonRatings::load()
{
	database()->load_common_ratings(this);
}