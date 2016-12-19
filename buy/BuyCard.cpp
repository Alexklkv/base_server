#include "BuyCard.h"
#include "../base/Log.h"
#include "../BaseCard.h"
#include "../BaseCardParams.h"
#include "../Player.h"
#include "../PricesParams.h"
#include "../LegendsServer.h"
#include "../TypesCache.h"

bool BuyCard::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	BaseCard::Grade grade = Enum<BaseCard::Grade>::wrap(data & 0x000000FF);
	bool is_async = Enum<BaseCard::Grade>::wrap(data & 0x0000FF00);
	auto &PRICES = is_async ? PricesParams::CARD_PRICES : PricesParams::CARD_ASYNC_PRICES;
	auto price_iter = PRICES.find(grade);
	if (price_iter == PRICES.end())
	{
		logger()->warning("Client %" PRIu32 " tried to buy card with wrong grade %" PRIu8, client->get_id(), grade);
		return false;
	}
	return true;
}

void BuyCard::get_price(const Client*, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	BaseCard::Grade grade = Enum<BaseCard::Grade>::wrap(data & 0x000000FF);
	uint8_t by_gold = (data >> 8);
	auto price_iter = PricesParams::CARD_PRICES.find(grade);
	gold_price = by_gold ? price_iter->second.gold : 0;
	souls_price = by_gold ? 0 : price_iter->second.souls;
}

void BuyCard::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	BaseCard::Grade grade = Enum<BaseCard::Grade>::wrap(data & 0x000000FF);
	auto &types = types_cache()->get(CardMask().set(grade))->select();
	if (types.empty())
	{
		logger()->warning("There is no cards selection for grade %" PRIu8, grade);
		data = BaseCardParams::CARDS_COUNT;
		return;
	}
	auto type = *std::next(types.begin(), Random::uint(types.size()));
	client->player->add_card(AwardReason::BUY, type);
	data = type;
}