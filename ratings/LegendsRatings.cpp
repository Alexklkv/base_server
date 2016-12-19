#include "LegendsRatings.h"

#include "Players.h"
#include "RatingsParams.h"

#include "../LegendsServer.h"
#include "../Player.h"

LegendsRatings::LegendsRatings(Category category, uint8_t type, const char *name):
	Ratings(name, RatingsParams::PLACES[category]),
	Thread(name, config()->RATINGS_UPDATE_TIMEOUT),
	category(category),
	type(type)
{}

LegendsRatings::~LegendsRatings()
{}

void LegendsRatings::clear() const
{
	for (auto iter = this->get_records(0)->begin(); iter != this->get_records(0)->end(); ++iter)
	{
		Player *player = static_cast<Player*>(players()->get((*iter)->player_id, false));
		if (player == nullptr)
			continue;

		player->rating_place_clear(this->category, this->type);
	}
}

void LegendsRatings::on_timeout()
{
	this->update();
}