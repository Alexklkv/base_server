#include "BuyLocationUnlock.h"

bool BuyLocationUnlock::check(const Client*, uint32_t, uint32_t, const client::Group*)
{
	return false;
}

void BuyLocationUnlock::get_price(const Client*, uint32_t&, uint32_t &souls_price, uint32_t, const client::Group*)
{
	souls_price = 0;
}

void BuyLocationUnlock::give(Client*, uint32_t, uint32_t&, const client::Group*, server::Group&)
{
}