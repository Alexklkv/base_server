#include "ApiBalance.h"

#include "Api.h"
#include "BaseConfig.h"
#include "BaseDatabase.h"
#include "BasePlayer.h"
#include "BaseServer.h"
#include "Log.h"
#include "QueryData.h"
#include "QueryParams.h"

#include <string.h>

static size_t on_read(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t length = size * nmemb;
	if (length == 0)
		return 0;

	ApiBalance *balance = static_cast<ApiBalance*>(stream);
	balance->read(ptr, length);

	return length;
}

ApiBalance::ApiBalance(Type type):
	Thread("ApiBalance"), curl(nullptr), worker(nullptr)
{
	this->curl = curl_easy_init();

	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, on_read);
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, this);

	this->buffer.push_back(0);

	switch (type)
	{
		case TYPE_DB:
			this->worker = &ApiBalance::get_orders_db;
			break;
		case TYPE_FS:
			this->worker = &ApiBalance::get_orders_fs;
			break;
	}
}

ApiBalance::~ApiBalance()
{
	curl_easy_cleanup(this->curl);
}

void ApiBalance::refill(BasePlayer *player)
{
	ApiQuery query;
	query.inner_id = player->inner_id;
	query.type = player->type;
	query.net_id = player->net_id;
	query.player = player;

	this->add(query);
}

void ApiBalance::get_orders_db(ApiQuery &query)
{
	orders_t orders;
	offers_t offers;

	uint32_t last_order = base_database()->load_orders(query.player, orders, offers);
	if (last_order == 0)
		return;

	query.player->last_order = last_order;

	for (auto iter = orders.begin(); iter != orders.end(); ++iter)
	{
		uint32_t order = iter->balance;
		uint8_t bonus = query.player->calc_bonus(order);

		query.player->add_balance(order + (order * bonus) / 100, config()->OFFER_NONE);
	}

	std::vector<bool> used_offers(config()->OFFERS_MAX_TYPE, false);

	for (auto iter = offers.begin(); iter != offers.end(); ++iter)
	{
		if (iter->type >= config()->OFFERS_MAX_TYPE)
		{
			logger()->warning("Incorrect offer type %u for player %u", iter->type, query.player->inner_id);
			continue;
		}

		uint32_t order = iter->balance;

		used_offers[iter->type] = true;

		query.player->add_balance(order, iter->type);
	}

	query.player->update_offers(used_offers);
}

void ApiBalance::get_orders_fs(ApiQuery &query)
{
	QueryParams params1;
	params1["userId"] = query.net_id;

	if (!Api::execute(this->curl, &query, "Billing.getAppUserBalanceAny", params1))
		return;

	uint32_t money = this->data()->get_uint32("/response");
	if (money == 0)
		return;

	QueryParams params2;
	params2["userId"] = query.net_id;
	params2["money"] = money;

	if (!Api::execute(this->curl, &query, "Billing.withDrawMoneySafe", params2))
		return;

	uint32_t balance = this->data()->get_uint32("/response/transferred");
	if (balance == 0)
		return;

	balance *= config()->FS_TO_BALANCE;
	uint8_t bonus = query.player->calc_bonus(balance);

	balance += (balance * bonus) / 100;
	query.player->add_balance(balance, false);
}

shared_ptr<QueryData> ApiBalance::data()
{
	QueryData *data = new QueryData;
	shared_ptr<QueryData> data_ptr(data);

	char *content = this->buffer.data();

	data_ptr->load(content, this->buffer.size() - 1);

	this->buffer.clear();
	this->buffer.push_back(0);

	return data_ptr;
}

void ApiBalance::add(ApiQuery &query)
{
	logger()->debug("Api balance got query for player %lu:%u (%lu total)", query.net_id, query.type, this->queries.unsafe_size());

	this->queries.push(query);

	this->notify();
}

void ApiBalance::on_notify()
{
	ApiQuery query;
	while (this->queries.try_pop(query))
	{
		logger()->debug("Api balance will execute worker for player %lu:%u", query.net_id, query.type);
		(this->*worker)(query);
	}
}

void ApiBalance::read(void *data, size_t size)
{
	size_t cur_size = this->buffer.size() - 1;
	this->buffer.resize(cur_size + size + 1, 0);

	memcpy(this->buffer.data() + cur_size, data, size);
}