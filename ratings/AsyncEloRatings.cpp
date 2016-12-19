#include "AsyncEloRatings.h"

#include "RatingsParams.h"

#include "../Database.h"
#include "../LegendsServer.h"

AsyncEloRatings::AsyncEloRatings(EloCategory elo_category, bool is_current):
	LegendsRatings(LegendsRatings::RATINGS_ELO_ASYNC, elo_category, RatingsParams::ELO_TABLES[elo_category]),
	is_current(is_current)
{}

BaseRatingRecord* AsyncEloRatings::create_record() const
{
	return new BaseRatingRecord;
}

void AsyncEloRatings::load()
{
	database()->load_async_elo_ratings(this);
}

void AsyncEloRatings::on_notify()
{
	this->update();
	elo_rewarder(Enum<EloCategory>::wrap(this->type))->notify();
}