#include "BuyCardUpgradeSlot.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../PricesParams.h"

bool BuyCardUpgradeSlot::check(const Client *client, uint32_t, uint32_t, const client::Group*)
{
	return (client->player->get_slots() < Player::MAX_SLOTS);
}

void BuyCardUpgradeSlot::get_price(const Client *client, uint32_t &gold_price, uint32_t &souls_price, uint32_t, const client::Group*)
{
	uint8_t next_slot = client->player->get_slots() + 1;
	auto price_iter = PricesParams::SLOTS_PRICES.find(next_slot);
	if (price_iter == PricesParams::SLOTS_PRICES.end())
	{
		logger()->warning("No price for slot %" PRIu8, next_slot);
		return;
	}
	gold_price = price_iter->second.gold;
	souls_price = price_iter->second.souls;
}

void BuyCardUpgradeSlot::give(Client* client, uint32_t, uint32_t &, const client::Group*, server::Group &)
{
	client->player->add_slot();
}