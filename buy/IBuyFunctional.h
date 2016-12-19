#pragma once
#include "../Client.h"
#include "base/client/Group.h"

class IBuyFunctional
{
public:
	virtual bool check(const Client *client, uint32_t, uint32_t data, const client::Group*) = 0;
	virtual void get_price(const Client *client, uint32_t &, uint32_t &souls_price, uint32_t data, const client::Group*) = 0;
	virtual void give(Client *client, uint32_t, uint32_t &data, const client::Group*, server::Group &) = 0;

};