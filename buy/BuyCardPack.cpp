#include "BuyCardPack.h"
#include "../base/Log.h"
#include "../CardPacks.h"
#include "../Player.h"
#include "../PricesParams.h"

bool BuyCardPack::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	CardPacks::Type type = Enum<CardPacks::Type>::wrap(data & 0x000000FF);
	if (type >= CardPacks::MAX_TYPE)
	{
		logger()->warning("Player %" PRIu32 " tried to buy boost pack with wrong type %" PRIu8, client->get_id(), type);
		return false;
	}
	return true;
}

void BuyCardPack::get_price(const Client*, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	CardPacks::Type type = Enum<CardPacks::Type>::wrap(data & 0x000000FF);
	uint8_t by_gold = (data >> 8);
	auto price_iter = PricesParams::CARD_PACK_PRICES.find(type);
	if (price_iter == PricesParams::CARD_PACK_PRICES.end())
	{
		logger()->warning("No price for card pack %" PRIu8, type);
		return;
	}
	gold_price = by_gold ? price_iter->second.gold : 0;
	souls_price = by_gold ? 0 : price_iter->second.souls;
}

void BuyCardPack::give(Client* client, uint32_t, uint32_t &data, const client::Group*, server::Group &server_data_group)
{
	client->player->generate_card_pack(AwardReason::BUY, Enum<CardPacks::Type>::wrap(data & 0x000000FF), server_data_group);
}