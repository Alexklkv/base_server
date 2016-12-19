#include "BuyAsyncShield.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../PricesParams.h"
#include "../AsyncShields.h"

bool BuyAsyncShield::check(const Client *client, uint32_t, uint32_t data, const client::Group*)
{
	AsyncShields::Type type = Enum<AsyncShields::Type>::wrap(data);
	if (!client->player->async_shields->can_buy(type))
	{
		logger()->warning("Client %" PRIu32 " tried buy unavailable async shield %" PRIu32, client->get_id(), data);
		return false;
	}
	return true;
}

void BuyAsyncShield::get_price(const Client *, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	auto price_iter = PricesParams::ASYNC_SHIELDS_PRICES.find(data);
	if (price_iter == PricesParams::ASYNC_SHIELDS_PRICES.end())
	{
		logger()->warning("No price for async shield %" PRIu32, data);
		return;
	}
	gold_price = price_iter->second.gold;
	souls_price = price_iter->second.souls;
}

void BuyAsyncShield::give(Client* client, uint32_t, uint32_t &data, const client::Group*, server::Group &)
{
	AsyncShields::Type type = Enum<AsyncShields::Type>::wrap(data);
	client->player->async_shields->activate(type);
}