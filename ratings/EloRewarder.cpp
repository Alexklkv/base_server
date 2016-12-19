#include "EloRewarder.h"

#include "Database.h"
#include "DelayedNotifications.h"
#include "Log.h"
#include "Notifications.h"
#include "Player.h"
#include "Players.h"

#include "../LegendsServer.h"

EloRewarder::EloRewarder(EloCategory category):
	Thread("EloRewarder", Config::ELO_REWARDER_TIMEOUT),
	category(category), last_award_time(0), awarded_count(0), changed_category_count(0)
{}

void EloRewarder::on_init()
{
	database()->load_last_elo_awards(this);
}

void EloRewarder::on_timeout()
{
	this->try_grant_prizes();
}

void EloRewarder::on_notify()
{
	this->grant_prizes();
}

void EloRewarder::try_grant_prizes()
{
	uint32_t award_time = this->get_award_time();
	auto ratings = legends_ratings(LegendsRatings::Category::RATINGS_ELO_PREVIOUS);
	auto ratings_async = legends_ratings(LegendsRatings::Category::RATINGS_ELO_ASYNC_PREVIOUS);

	if (last_award_time == award_time)
		return;

	ratings[this->category]->notify();
	ratings_async[this->category]->notify();
}

void EloRewarder::grant_prizes()
{
	uint32_t award_time = this->get_award_time();
	this->last_award_time = award_time;

	this->grant_prizes_elo();
	this->grant_prizes_elo_async();

	this->save();
	logger()->info("Elo category %" PRIu8 " winners rewarding finished", this->category);
}

void EloRewarder::grant_prizes_elo()
{
	auto ratings = legends_ratings(LegendsRatings::Category::RATINGS_ELO_PREVIOUS);

	uint16_t place = 1;
	uint16_t awarded_count = 0;
	uint16_t changed_category_count = 0;

	for (auto iter = ratings[this->category]->get_records(0)->begin(); iter != ratings[this->category]->get_records(0)->end(); ++iter)
	{
		Player *player = static_cast<Player*>(players()->get((*iter)->player_id, true));
		if (player == nullptr)
			continue;

		player->elo_rating_previous = player->elo_rating.load();
		if (player->try_change_elo_category())
			changed_category_count++;
		if (place > 50)
			break;

		if (player->elo_ratings_award(this->category, place))
			awarded_count++;

		place++;

		this->awarded_count = awarded_count;
		this->changed_category_count = changed_category_count;
	}

	logger()->info("Elo category %" PRIu8 " winners rewarding finished", this->category);
}

void EloRewarder::grant_prizes_elo_async()
{
	auto ratings = legends_ratings(LegendsRatings::Category::RATINGS_ELO_PREVIOUS);

	uint16_t changed_category_count = 0;

	for (auto iter = ratings[this->category]->get_records(0)->begin(); iter != ratings[this->category]->get_records(0)->end(); ++iter)
	{
		Player *player = static_cast<Player*>(players()->get((*iter)->player_id, true));
		if (player == nullptr)
			continue;

		player->elo_rating_previous = player->elo_rating.load();
		if (player->try_change_elo_category(true))
			changed_category_count++;

		this->awarded_async_count = 0;
		this->changed_category_async_count = changed_category_count;
	}

	logger()->info("Elo async category %" PRIu8 " winners rewarding finished", this->category);
}

uint32_t EloRewarder::get_award_time() const
{
	time_t now = time(nullptr);
	tm current_tm;
	localtime_r(&now, &current_tm);

	uint8_t cur_week_day = current_tm.tm_wday;
	current_tm.tm_hour = 0;
	current_tm.tm_min = 0;
	current_tm.tm_sec = 0;
	time_t week_end = mktime(&current_tm);
	week_end += 24 * 60 * 60 * (1 - cur_week_day) + 5 * 60;

	return week_end;
}

void EloRewarder::save()
{
	database()->save_last_elo_awards(this);
}