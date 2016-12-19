#include "BuyTotemAllowParallel.h"
#include "../base/Log.h"
#include "../BaseCard.h"
#include "../Player.h"
#include "../Totems.h"

bool BuyTotemAllowParallel::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	if (data >= BaseCard::MAX_FRACTION)
	{
		logger()->warning("Player %" PRIu32 " tried to upgrade totem for wrong fraction %" PRIu32, client->get_id(), data);
		return false;
	}
	bool can = client->player->totems->can_parallel(static_cast<BaseCard::Fraction>(data));
	if (!can)
		logger()->warning("Fail buying parallel upgrade. Totem already can parallel");
	return can;
}

void BuyTotemAllowParallel::get_price(const Client* client, uint32_t&, uint32_t& souls_price, uint32_t data, const client::Group*)
{
	client->player->totems->get_parallel_price(static_cast<BaseCard::Fraction>(data), souls_price);
}

void BuyTotemAllowParallel::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	client->player->totems->allow_parallel_upgrading(static_cast<BaseCard::Fraction>(data));
}