#pragma once

#include "ApiQuery.h"
#include "Thread.h"

#include <vector>

#include <boost/shared_ptr.hpp>

#include <concurrent_queue.h>

#include <curl/curl.h>

class BasePlayer;
class QueryData;

using boost::shared_ptr;

class ApiBalance : public Thread
{
	friend class Api;

private:
	enum Type : uint8_t
	{
		TYPE_DB,
		TYPE_FS
	};

	typedef void (ApiBalance::*worker_t)(ApiQuery &);

	typedef tbb::concurrent_queue<ApiQuery> queries_t;
	typedef std::vector<char> buffer_t;

	CURL *curl;
	queries_t queries;
	buffer_t buffer;
	worker_t worker;

	shared_ptr<QueryData> data();
	void add(ApiQuery &query);

	void get_orders_db(ApiQuery &query);
	void get_orders_fs(ApiQuery &query);

protected:
	void on_notify();

public:
	enum ProviderType : uint8_t
	{
		PROVIDER_VK	= 0,
		PROVIDER_MM	= 1,
		PROVIDER_OK	= 4,
		PROVIDER_FB	= 5,
		PROVIDER_MB	= 6,
		PROVIDER_FS	= 30,
		PROVIDER_NG	= 31,
		PROVIDER_RG	= 32,
		PROVIDER_FL	= 36,
		PROVIDER_APPLE	= 40
	};

	struct Order
	{
		uint32_t balance;
		uint8_t provider;
	};

	struct Offer
	{
		uint32_t balance;
		uint8_t provider;
		uint8_t type;
	};

	typedef std::vector<Order> orders_t;
	typedef std::vector<Offer> offers_t;

	explicit ApiBalance(Type type);
	~ApiBalance();

	void refill(BasePlayer *player);
	void read(void *data, size_t size);
};