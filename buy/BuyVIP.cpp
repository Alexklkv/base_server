#include "BuyVIP.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../PricesParams.h"
#include "../Items.h"

bool BuyVIP::check(const Client* client, uint32_t, uint32_t, const client::Group*)
{
	time_t current_time = time(nullptr);
	if (client->has_vip(current_time))
	{
		logger()->warning("Player %" PRIu32 " tried to buy vip when old is not expired", client->get_id());
		return false;
	}
	return true;
}

void BuyVIP::get_price(const Client*, uint32_t &, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	auto price_iter = PricesParams::VIP_PRICES.find(data);
	if (price_iter == PricesParams::VIP_PRICES.end())
	{
		logger()->warning("No price for %" PRIu8 "days VIP", data);
		return;
	}
	souls_price = price_iter->second.souls;
}

void BuyVIP::give(Client* client, uint32_t, uint32_t &data, const client::Group*, server::Group &server_data_group)
{
	client->player->add_vip(data * Config::DAY);
	auto vip_sharps = Items::pick_vip_sharps();
	for (auto sharp_type : vip_sharps)
	{
		client->player->items->add(AwardReason::BUY, sharp_type, 1);
		server_data_group.add(static_cast<uint32_t>(enum_unwrap(sharp_type)));
		server_data_group.next();
	}
}