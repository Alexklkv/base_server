#include "BuyGoldPack.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../PricesParams.h"
#include "../Items.h"

bool BuyGoldPack::check(const Client *, uint32_t, uint32_t data, const client::Group*)
{
	auto price_iter = PricesParams::GOLD_PACK_PRICES.find(data);
	if (price_iter == PricesParams::GOLD_PACK_PRICES.end())
	{
		logger()->warning("No price for gold pack of size %" PRIu8, data);
		return false;
	}
	return true;
}

void BuyGoldPack::get_price(const Client *, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	auto price_iter = PricesParams::GOLD_PACK_PRICES.find(data);
	if (price_iter == PricesParams::GOLD_PACK_PRICES.end())
	{
		logger()->warning("No price for gold pack of size %" PRIu8, data);
		return;
	}
	gold_price = price_iter->second.gold;
	souls_price = price_iter->second.souls;
}

void BuyGoldPack::give(Client* client, uint32_t, uint32_t &data, const client::Group*, server::Group &)
{
	client->player->add_balance(AwardReason::BUY, data, 0);
}