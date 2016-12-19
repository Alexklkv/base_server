#pragma once

#include "NoCopy.h"
#include "QueryStatistic.h"

#include <concurrent_queue.h>

namespace mysqlpp
{
	class Connection;
	class Row;
	class SimpleResult;
	class SQLQueryParms;
	class StoreQueryResult;
}

class BaseConfig;

using mysqlpp::Connection;
using mysqlpp::SimpleResult;
using mysqlpp::SQLQueryParms;
using mysqlpp::StoreQueryResult;

class DatabaseManager : private NoCopy
{
private:
	tbb::concurrent_queue<Connection*> connections;

	QueryStatistic statistic;

	const BaseConfig *config;

	Connection* get();
	void add(Connection *connection);
	void connect(Connection *connection) const;

public:
	DatabaseManager(const BaseConfig *config);
	virtual ~DatabaseManager();

	virtual StoreQueryResult store(const std::string &str, SQLQueryParms *params, const char *hash);
	virtual SimpleResult execute(const std::string &str, SQLQueryParms *params, const char *hash);
	virtual std::string escape(std::string str);
};