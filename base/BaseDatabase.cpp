#include "BaseDatabase.h"

#include "BaseConfig.h"
#include "BasePlayer.h"
#include "BaseServer.h"
#include "Blocks.h"
#include "Counters.h"
#include "Log.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <query.h>
#pragma GCC diagnostic pop

using std::string;
using std::stringstream;

BaseDatabase::BaseDatabase(DatabaseManager *manager):
	db(manager)
{}

BaseDatabase::~BaseDatabase()
{}

StoreQueryResult BaseDatabase::store(const std::string &str, SQLQueryParms *params, const char *hash)
{
	return this->db->store(str, params, hash);
}

SimpleResult BaseDatabase::execute(const std::string &str, SQLQueryParms *params, const char *hash)
{
	return this->db->execute(str, params, hash);
}

std::string BaseDatabase::escape(const std::string &str)
{
	return this->db->escape(str);
}

BasePlayer* BaseDatabase::create_player(uint64_t net_id, Api::Type type)
{
	uint32_t register_time = time(nullptr);

	SQLQueryParms params = SQLQueryParms() << net_id << static_cast<uint16_t>(type) << register_time;
	SimpleResult result = this->execute("INSERT INTO players SET net_id = %0q, type = %1q, register_time = FROM_UNIXTIME(%2q)", &params);

	return this->create_player(result.insert_id(), net_id, type, register_time);
}

BasePlayer* BaseDatabase::load_player(uint32_t inner_id)
{
	SQLQueryParms params = SQLQueryParms() << inner_id;

	StoreQueryResult result = this->store("SELECT *, UNIX_TIMESTAMP(register_time) as reg_time FROM players WHERE inner_id = %0q LIMIT 1", &params);
	if (!result || result.empty())
		return nullptr;

	return this->create_player(result[0]);
}

BasePlayer* BaseDatabase::load_player(uint64_t net_id, Api::Type type, bool create)
{
	SQLQueryParms params = SQLQueryParms() << net_id << static_cast<uint16_t>(type);

	StoreQueryResult result = this->store("SELECT *, UNIX_TIMESTAMP(register_time) as reg_time FROM players WHERE net_id = %0q AND type = %1q LIMIT 1", &params);
	if (!result || result.empty())
	{
		if (create)
			return this->create_player(net_id, type);
		return nullptr;
	}

	return this->create_player(result[0]);
}

void BaseDatabase::load_players(const std::vector<uint32_t> &inner_ids, std::vector<BasePlayer*> &players)
{
	if (inner_ids.empty())
		return;

	stringstream query;
	query << "SELECT *, UNIX_TIMESTAMP(register_time) as reg_time FROM players WHERE inner_id IN (";

	for (auto iter = inner_ids.begin(); iter != inner_ids.end(); ++iter)
	{
		query << *iter;

		if (iter == inner_ids.end() - 1)
			continue;

		query << ",";
	}

	query << ")";

	StoreQueryResult result = this->store(query.str());
	if (!result)
		return;

	for (const auto &iter : result)
	{
		BasePlayer *player = this->create_player(iter);
		players.push_back(player);
	}
}

void BaseDatabase::load_players_ids(const std::vector<uint64_t> &net_ids, Api::Type type, std::vector<uint32_t> &inner_ids)
{
	if (net_ids.empty())
		return;

	stringstream query;
	query << "SELECT inner_id FROM players WHERE type = %0q AND net_id IN (";

	for (auto iter = net_ids.begin(); iter != net_ids.end(); ++iter)
	{
		query << *iter;

		if (iter == net_ids.end() - 1)
			continue;

		query << ",";
	}

	query << ")";

	SQLQueryParms params = SQLQueryParms() << static_cast<uint16_t>(type);

	StoreQueryResult result = this->store(query.str(), &params);
	if (!result)
		return;

	for (const auto &iter : result)
		inner_ids.push_back(iter["inner_id"]);
}

void BaseDatabase::load_counters(Counters *counters)
{
	StoreQueryResult result = this->store("SELECT * FROM counters_daily WHERE date = CURDATE()");
	if (!result)
		return;

	size_t rows = result.num_rows();
	for (size_t i = 0; i < rows; i++)
		counters->set(result[i]["type"], result[i]["data"], result[i]["value"]);
}

int BaseDatabase::load_orders(const BasePlayer *player, ApiBalance::orders_t &orders, ApiBalance::offers_t &offers)
{
	SQLQueryParms params = SQLQueryParms() << player->net_id << player->type << player->last_order;

	StoreQueryResult result = this->store("SELECT * FROM orders WHERE net_id = %0q AND type = %1q AND id > %2q ORDER BY id ASC", &params);
	if (!result)
		return 0;

	uint32_t last_order = 0;
	size_t rows = result.num_rows();

	for (size_t i = 0; i < rows; i++)
	{
		last_order = result[i]["id"];

		uint8_t offer = result[i]["offer"];
		if (offer == 0)
			orders.push_back({result[i]["amount"], result[i]["provider_id"]});
		else
			offers.push_back({result[i]["amount"], result[i]["provider_id"], offer});
	}

	return last_order;
}

void BaseDatabase::save_blocks(Blocks *blocks)
{
	stringstream query;

	Blocks::Block block;
	while (blocks->blocks.try_pop(block))
	{
		if (query.tellp() > 0)
			query << ",";

		query << "(" << static_cast<uint32_t>(block.reason) << "," << static_cast<uint32_t>(block.repeated) << "," << block.judge << "," << block.target << "," << block.time << ")";
	}

	if (query.tellp() <= 0)
		return;

	this->execute("INSERT INTO blocks (reason, repeated, judge, target, time) VALUES" + query.str());
}

void BaseDatabase::save_counters(const Counters *counters)
{
	stringstream query, query_daily;

	for (size_t type = 0; type < counters->max_type; type++)
	{
		const Counters::counters_t *values = &(counters->values[type]);

		for (auto iter = values->begin(); iter != values->end(); ++iter)
		{
			const Counters::Counter *counter = &(iter->second);
			if (!counter->changed)
				continue;

			if (counters->is_daily(type))
			{
				if (query_daily.tellp() > 0)
					query_daily << ",";
				query_daily << "(" << type << "," << iter->first << ", CURDATE(), " << static_cast<int64_t>(counter->value) << ")";
			}
			else
			{
				if (query.tellp() > 0)
					query << ",";
				query << "(" << type << "," << iter->first << "," << static_cast<int64_t>(counter->value) << ")";
			}
		}
	}

	if (query.tellp() > 0)
		this->execute("INSERT INTO counters (type, data, value) VALUES" + query.str());
	if (query_daily.tellp() > 0)
		this->execute("REPLACE INTO counters_daily (type, data, date, value) VALUES" + query_daily.str());
}