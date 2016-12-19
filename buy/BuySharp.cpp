#include "BuySharp.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../Items.h"
#include "../PricesParams.h"

bool BuySharp::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	ItemType sharp_item = Enum<ItemType>::wrap(data & 0x000000FF);
	if (Items::get_category(sharp_item) != Items::SHARP)
	{
		logger()->warning("Client %" PRIu32 " tried buy wrong sharp item %" PRIu8, client->get_id(), sharp_item);
		return false;
	}
	return true;
}

void BuySharp::get_price(const Client*, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	ItemType sharp_item = Enum<ItemType>::wrap(data & 0x000000FF);
	uint8_t count = (data >> 8);
	auto price_iter = PricesParams::SHARP_PRICES.find(sharp_item);
	if (price_iter == PricesParams::SHARP_PRICES.end())
	{
		logger()->warning("No price for sharp item %" PRIu8, sharp_item);
		return;
	}
	gold_price = price_iter->second.gold * count;
	souls_price = price_iter->second.souls * count;
}

void BuySharp::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	ItemType sharp_item = Enum<ItemType>::wrap(data & 0x000000FF);
	uint8_t count = (data >> 8);
	client->player->items->add(AwardReason::BUY, sharp_item, count);
}