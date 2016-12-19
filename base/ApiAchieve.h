#pragma once

#include "ApiQuery.h"
#include "Thread.h"

#include <boost/shared_ptr.hpp>

#include <concurrent_queue.h>

#include <curl/curl.h>

class BasePlayer;
class QueryData;

using boost::shared_ptr;

class ApiAchieve : public Thread
{
	friend class Api;

private:
	typedef tbb::concurrent_queue<ApiQuery> queries_t;

	CURL *curl;
	queries_t queries;

protected:
	void on_notify();

public:
	ApiAchieve();
	~ApiAchieve();

	void set(const BasePlayer *player, uint16_t achieve_id);
};