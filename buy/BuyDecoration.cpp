#include "BuyDecoration.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../Decoration.h"
#include "../DecorationParams.h"
#include "../PricesParams.h"
#include "../LegendsServer.h"

bool BuyDecoration::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	Decoration::Object object = Enum<Decoration::Object>::wrap(data & 0x000000FF);
	uint8_t type = (data >> 8);
	if (decoration_params()->get(object, type) == nullptr)
	{
		logger()->warning("Player %" PRIu32 " tried to buy wrong decoration object %" PRIu8 " type %" PRIu8, client->get_id(), object, type);
		return false;
	}
	if (client->player->decoration->has(object, type))
	{
		logger()->warning("Player %" PRIu32 " tried to buy decoration object %" PRIu8 " type %" PRIu8 " that he had already had", client->get_id(), object, type);
		return false;
	}
	logger()->debug("Player %" PRIu32 " wants to buy decoration object %" PRIu8 " type %" PRIu8, client->get_id(), object, type);
	return true;
}

void BuyDecoration::get_price(const Client*, uint32_t &gold_price, uint32_t&, uint32_t data, const client::Group*)
{
	Decoration::Object object = Enum<Decoration::Object>::wrap(data & 0x000000FF);
	if (object != Decoration::WALLPAPER)
		gold_price = PricesParams::DECORATION_GOLD_PRICE;
}

void BuyDecoration::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	Decoration::Object object = static_cast<Decoration::Object>(data & 0x000000FF);
	uint8_t type = (data >> 8);
	client->player->decoration->add(object, type);
}