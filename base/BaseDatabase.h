#pragma once

#include "Api.h"
#include "ApiBalance.h"
#include "DatabaseManager.h"
#include "NoCopy.h"

#include <vector>

class BasePlayer;
class Blocks;
class Counters;
class DatabaseManager;
class Friends;

class BaseDatabase : private NoCopy
{
private:
	DatabaseManager *const db;

protected:
	StoreQueryResult store(const std::string &str, SQLQueryParms *params = nullptr, const char *hash = nullptr);
	SimpleResult execute(const std::string &str, SQLQueryParms *params = nullptr, const char *hash = nullptr);
	std::string escape(const std::string &str);

public:
	BaseDatabase(DatabaseManager *manager);
	virtual ~BaseDatabase();

	virtual BasePlayer* create_player(const mysqlpp::Row &row) = 0;
	virtual BasePlayer* create_player(uint32_t inner_id, uint64_t net_id, Api::Type type, uint32_t register_time) = 0;

	BasePlayer* create_player(uint64_t net_id, Api::Type type);

	BasePlayer* load_player(uint64_t net_id, Api::Type type, bool create);
	BasePlayer* load_player(uint32_t inner_id);
	void load_players(const std::vector<uint32_t> &inner_ids, std::vector<BasePlayer*> &players);
	void load_players_ids(const std::vector<uint64_t> &net_ids, Api::Type type, std::vector<uint32_t> &inner_ids);

	void load_counters(Counters *counters);

	int load_orders(const BasePlayer *player, ApiBalance::orders_t &orders, ApiBalance::offers_t &offers);

	void save_blocks(Blocks *blocks);
	void save_counters(const Counters *counters);
};