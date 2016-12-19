#pragma once

#include "EloRatings.h"
#include "Thread.h"

#include "../enums.h"

class EloRewarder : public Thread
{
	friend class Database;
	friend class EloRatings;
	friend class AsyncEloRatings;

private:
	const EloCategory category;

	uint32_t last_award_time;

	uint16_t awarded_count;
	uint16_t changed_category_count;
	uint16_t awarded_async_count;
	uint16_t changed_category_async_count;

protected:
	void on_timeout();
	void on_init();
	void on_notify();
	void save();

	void try_grant_prizes();
	void grant_prizes();
	void grant_prizes_elo();
	void grant_prizes_elo_async();

public:
	EloRewarder(EloCategory category);

	uint32_t get_award_time() const;
};