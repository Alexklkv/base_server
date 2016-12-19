#include "BuyTotemUpgrade.h"
#include "../base/Log.h"
#include "../BaseCard.h"
#include "../Player.h"
#include "../Totems.h"

bool BuyTotemUpgrade::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	if (data >= BaseCard::MAX_FRACTION)
	{
		logger()->warning("Player %" PRIu32 " tried to upgrade totem for wrong fraction %" PRIu32, client->get_id(), data);
		return false;
	}
	bool can = client->player->totems->can_upgrade(static_cast<BaseCard::Fraction>(data));
	if (!can)
		logger()->warning("Fail buying totem upgrade. Totem can't upgrade");
	return can;
}

void BuyTotemUpgrade::get_price(const Client* client, uint32_t&, uint32_t& souls_price, uint32_t data, const client::Group*)
{
	float respect_price = .0f;
	client->player->totems->get_upgrade_price(static_cast<BaseCard::Fraction>(data), souls_price, respect_price);
}

void BuyTotemUpgrade::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	client->player->totems->upgrade(static_cast<BaseCard::Fraction>(data));
}