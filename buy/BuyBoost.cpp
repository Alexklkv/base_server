#include "BuyBoost.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../Boosters.h"
#include "../Items.h"
#include "../PricesParams.h"

bool BuyBoost::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	ItemType boost_item = Enum<ItemType>::wrap(data & 0x000000FF);
	if (Items::get_category(boost_item) != Items::BOOST)
	{
		logger()->warning("Client %" PRIu32 " tried buy wrong boost item %" PRIu8, client->get_id(), boost_item);
		return false;
	}
	return true;
}

void BuyBoost::get_price(const Client*, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	ItemType boost_item = Enum<ItemType>::wrap(data & 0x000000FF);
	auto price_iter = PricesParams::BOOST_PRICES.find(boost_item);
	if (price_iter == PricesParams::BOOST_PRICES.end())
	{
		logger()->warning("No price for boost item %" PRIu8, boost_item);
		return;
	}
	gold_price = price_iter->second.gold;
	souls_price = price_iter->second.souls;
}

void BuyBoost::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	ItemType boost_item = Enum<ItemType>::wrap(data & 0x000000FF);
	time_t current_time = time(nullptr);
	client->player->boosters->add(boost_item, current_time, client->player->vip_left(current_time), 0, 0);
}