#include "EloRatings.h"

#include "RatingsParams.h"

#include "../Database.h"
#include "../LegendsServer.h"

EloRatings::EloRatings(EloCategory elo_category, bool is_current):
	LegendsRatings(LegendsRatings::RATINGS_ELO, elo_category, RatingsParams::ELO_TABLES[elo_category]),
	is_current(is_current)
{}

BaseRatingRecord* EloRatings::create_record() const
{
	return new BaseRatingRecord;
}

void EloRatings::load()
{
	database()->load_elo_ratings(this);
}

void EloRatings::on_notify()
{
	this->update();
	elo_rewarder(Enum<EloCategory>::wrap(this->type))->notify();
}