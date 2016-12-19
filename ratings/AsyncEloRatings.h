#pragma once

#include "EloRewarder.h"
#include "LegendsRatings.h"

#include "../enums.h"

class AsyncEloRatings : public LegendsRatings
{
	friend class EloRewarder;

protected:

	BaseRatingRecord* create_record() const override;

	void load() override;
	void on_notify();

public:
	const bool is_current;

	AsyncEloRatings(EloCategory elo_category, bool is_current);
};