#pragma once

#include "CommonRatings.h"
#include "LegendsRatings.h"

#include "../enums.h"

#include <set>
#include <string>

class RatingsParams
{
public:
	struct Params
	{
		const char* name;
		const char* table;
	};

	static const size_t PLACES[LegendsRatings::RATINGS_MAX_CATEGORY];

	static const Params COMMON_TABLES[CommonRatings::COMMON_MAX_TYPE];

	static const char *ELO_TABLES[ELO_MAX_CATEGORY];

	static const char *LOCATION_RATINGS_NAME;
};