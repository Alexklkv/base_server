#pragma once

#include "EloRewarder.h"
#include "LegendsRatings.h"

#include "../enums.h"

class EloRatings : public LegendsRatings
{
	friend class EloRewarder;

protected:

	BaseRatingRecord* create_record() const override;

	void load() override;
	void on_notify();

public:
	const bool is_current;

	EloRatings(EloCategory elo_category, bool is_current);

};