#pragma once

#include "LegendsRatings.h"

class CommonRatings : public LegendsRatings
{
private:
	BaseRatingRecord* create_record() const override;

	void load() override;

public:
	enum Type
	{
		COMMON_COMMON,
		COMMON_BATTLE,
		COMMON_RESPECT,

		COMMON_MAX_TYPE
	};

	CommonRatings(Type type, const char *name);
	virtual ~CommonRatings();
};