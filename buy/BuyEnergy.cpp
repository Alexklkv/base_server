#include "BuyEnergy.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../PricesParams.h"
#include "../Items.h"

bool BuyEnergy::check(const Client *client, uint32_t, uint32_t data, const client::Group*)
{
	ItemType energy_item = Enum<ItemType>::wrap(data);
	if (Items::get_category(energy_item) != Items::ENERGY || energy_item == ItemType::ENERGY_SMALL_POTION)
	{
		logger()->warning("Client %" PRIu32 " tried buy wrong energy item %" PRIu8, client->get_id(), energy_item);
		return false;
	}
	return true;
}

void BuyEnergy::get_price(const Client *, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	ItemType energy_item = Enum<ItemType>::wrap(data);
	auto price_iter = PricesParams::ENERGY_PRICES.find(energy_item);
	if (price_iter == PricesParams::ENERGY_PRICES.end())
	{
		logger()->warning("No price for energy item %" PRIu8, energy_item);
		return;
	}
	gold_price = price_iter->second.gold;
	souls_price = price_iter->second.souls;
}

void BuyEnergy::give(Client* client, uint32_t, uint32_t &data, const client::Group*, server::Group &)
{
	ItemType energy_item = Enum<ItemType>::wrap(data);
	client->player->items->add(AwardReason::BUY, energy_item, 1);
}