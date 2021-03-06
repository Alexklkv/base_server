#include "BuyTotemBoost.h"
#include "../base/Log.h"
#include "../BaseCard.h"
#include "../Player.h"
#include "../Totems.h"

bool BuyTotemBoost::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	if (data >= BaseCard::MAX_FRACTION)
	{
		logger()->warning("Player %" PRIu32 " tried to upgrade totem for wrong fraction %" PRIu32, client->get_id(), data);
		return false;
	}
	bool can = client->player->totems->can_boost(static_cast<BaseCard::Fraction>(data));
	if (!can)
		logger()->warning("Fail buying boost. Totem can't boost");
	return can;
}

void BuyTotemBoost::get_price(const Client* client, uint32_t&, uint32_t& souls_price, uint32_t data, const client::Group*)
{
	client->player->totems->get_boost_price(static_cast<BaseCard::Fraction>(data), souls_price);
}

void BuyTotemBoost::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	client->player->totem_boost(static_cast<BaseCard::Fraction>(data), 20);
}