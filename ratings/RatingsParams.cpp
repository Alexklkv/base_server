#include "RatingsParams.h"

const size_t RatingsParams::PLACES[LegendsRatings::RATINGS_MAX_CATEGORY]
{
	9,	// RATINGS_COMMON
	3,	// RATINGS_LOCATIONS
	10,	// RATINGS_ELO
};

const RatingsParams::Params RatingsParams::COMMON_TABLES[CommonRatings::COMMON_MAX_TYPE] =
{
	{"Common rating", "ratings_common"},
	{"Battle rating", "ratings_battle"},
	{"Respect rating", "ratings_respect"}
};

const char *RatingsParams::ELO_TABLES[ELO_MAX_CATEGORY] =
{
	"Elo novice rating",	// ELO_NOVICE
	"Elo bronze rating",	// ELO_BRONZE
	"Elo silver rating",	// ELO_SILVER
	"Elo gold rating",	// ELO_GOLD
	"Elo legend rating",	// ELO_LEGEND
};

const char *RatingsParams::LOCATION_RATINGS_NAME = "Locations rating";