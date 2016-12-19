#pragma once
#include "IBuyFunctional.h"

class BuyEnergy: public IBuyFunctional
{
public:
	bool check(const Client *client, uint32_t, uint32_t data, const client::Group*) override;
	void get_price(const Client *client, uint32_t &, uint32_t &souls_price, uint32_t data, const client::Group*) override;
	void give(Client *client, uint32_t, uint32_t &data, const client::Group*, server::Group &) override;
};