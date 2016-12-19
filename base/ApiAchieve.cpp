#include "ApiAchieve.h"

#include "Api.h"
#include "BasePlayer.h"
#include "BaseServer.h"
#include "Log.h"
#include "QueryData.h"
#include "QueryParams.h"

#include <curl/curl.h>

ApiAchieve::ApiAchieve():
	Thread("ApiAchieve"), curl(nullptr)
{
	this->curl = curl_easy_init();
}

ApiAchieve::~ApiAchieve()
{
	curl_easy_cleanup(this->curl);
}

void ApiAchieve::set(const BasePlayer *player, uint16_t achieve_id)
{
	if (player->type != Api::TYPE_FS)
		return;

	ApiQuery query;
	query.type = player->type;
	query.net_id = player->net_id;
	query.inner_id = achieve_id;

	this->queries.push(query);

	this->notify();
}

void ApiAchieve::on_notify()
{
	ApiQuery query;
	while (this->queries.try_pop(query))
	{
		QueryParams params;
		params["userId"] = query.net_id;
		params["achievId"] = query.inner_id;

		Api::execute(this->curl, &query, "User.giveAchievment", params);

		logger()->debug("Api achieve will set for player %lu:%u", query.net_id, query.type);
	}
}