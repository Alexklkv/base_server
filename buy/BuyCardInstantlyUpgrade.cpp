#include "BuyCardInstantlyUpgrade.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../Cards.h"

bool BuyCardInstantlyUpgrade::check(const Client *client, uint32_t, uint32_t data, const client::Group*)
{
	auto card = client->player->cards->get_card(data);
	if (card == nullptr)
	{
		logger()->warning("Player %" PRIu32 " tried to upgrade nonexistent card %" PRIu32, client->get_id(), data);
		return false;
	}
	return (card->get_block_expires() > 0);
}

void BuyCardInstantlyUpgrade::get_price(const Client *client, uint32_t &, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	client->player->cards->get_instantly_upgrade_price(data, souls_price);
}

void BuyCardInstantlyUpgrade::give(Client* client, uint32_t, uint32_t &data, const client::Group*, server::Group &)
{
	client->player->cards->set_complete_upgrade_time(data);
}