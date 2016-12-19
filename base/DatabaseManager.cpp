#include "DatabaseManager.h"

#include "BaseConfig.h"
#include "Log.h"

#include <connection.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <query.h>
#pragma GCC diagnostic pop

#include <sys/time.h>

using std::string;
using std::stringstream;

using mysqlpp::ConnectTimeoutOption;
using mysqlpp::MultiStatementsOption;
using mysqlpp::Query;
using mysqlpp::BadQuery;

DatabaseManager::DatabaseManager(const BaseConfig *config):
	statistic(config->DATABASE_STATISTIC), config(config)
{
	if (!Connection::thread_aware())
	{
		logger()->error("MySQL++ implementation used is not thread-aware");
	}
}

DatabaseManager::~DatabaseManager()
{
	Connection *connection;
	while (this->connections.try_pop(connection))
	{
		connection->disconnect();
		delete connection;
	}
}

Connection* DatabaseManager::get()
{
	Connection *connection;
	if (this->connections.try_pop(connection))
	{
		connection->thread_start();
		return connection;
	}

	connection = new Connection;
	if (this->config->DATABASE_TIMEOUT != 0)
		connection->set_option(new ConnectTimeoutOption(this->config->DATABASE_TIMEOUT));

	connection->set_option(new MultiStatementsOption(true));

	this->connect(connection);
	return connection;
}

void DatabaseManager::connect(Connection *connection) const
{
	while (true)
	{
		try
		{
			connection->connect(this->config->DATABASE_NAME, this->config->DATABASE_HOST, this->config->DATABASE_USER, this->config->DATABASE_PASSWORD, this->config->DATABASE_PORT);
		}
		catch (...)
		{}

		if (connection->connected())
		{
			logger()->debug("MySQL connection opened with %s:%d", this->config->DATABASE_HOST, this->config->DATABASE_PORT);
			return;
		}

		logger()->warning("Failed to connect to MySQL server, %s", connection->error());
		sleep(5);
	}
}

void DatabaseManager::add(Connection *connection)
{
	connection->thread_end();
	this->connections.push(connection);
}

StoreQueryResult DatabaseManager::store(const string &str, SQLQueryParms *params, const char *hash)
{
	Connection *connection = this->get();

	StoreQueryResult result;

	timeval tv1;
	gettimeofday(&tv1, nullptr);

	while (true)
	{
		try
		{
			bool has_params = (params != nullptr);
			Query query = connection->query(has_params ? str.c_str() : nullptr);

			if (has_params)
			{
				query.parse();
				result = query.store(*params);
			}
			else
				result = query.store(str.c_str(), str.length());

			while (query.more_results())
				result = query.store_next();
		}
		catch (const BadQuery &e)
		{
			switch (e.errnum())
			{
				case 1205:		// Lock wait timeout exceeded; try restarting transaction
				case 1213:		// Deadlock found when trying to get lock
					logger()->warning("Query store finished with error %d, repeating", e.errnum());
					continue;
				case 2006:		// MySQL server has gone away
				case 2013:		// Lost connection to MySQL server during query
					logger()->debug("MySQL connection lost with error %d, repeating", e.errnum());
					this->connect(connection);
					continue;
			}
			logger()->warning("Failed to store query %s, error %d", str.c_str(), e.errnum());
		}
		break;
	}

	if (hash == nullptr)
		hash = str.c_str();

	timeval tv2;
	gettimeofday(&tv2, nullptr);
	this->statistic.add(hash, (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec));

	this->add(connection);
	return result;
}

SimpleResult DatabaseManager::execute(const string &str, SQLQueryParms *params, const char *hash)
{
	Connection *connection = this->get();

	SimpleResult result;

	timeval tv1;
	gettimeofday(&tv1, nullptr);

	while (true)
	{
		try
		{
			bool has_params = (params != nullptr);
			Query query = connection->query(has_params ? str.c_str() : nullptr);

			if (has_params)
			{
				query.parse();
				result = query.execute(*params);
			}
			else
				result = query.execute(str.c_str(), str.length());

			while (query.more_results())
				query.store_next();
		}
		catch (const BadQuery &e)
		{
			switch (e.errnum())
			{
				case 1205:		// Lock wait timeout exceeded; try restarting transaction
				case 1213:		// Deadlock found when trying to get lock
					logger()->warning("Query execute finished with error %d, repeating", e.errnum());
					continue;
				case 2006:		// MySQL server has gone away
				case 2013:		// Lost connection to MySQL server during query
					logger()->debug("MySQL connection lost with error %d, repeating", e.errnum());
					this->connect(connection);
					continue;
			}
			logger()->warning("Failed to execute query %s, error %d", str.c_str(), e.errnum());
		}
		break;
	}

	if (hash == nullptr)
		hash = str.c_str();

	timeval tv2;
	gettimeofday(&tv2, nullptr);
	this->statistic.add(hash, (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec));

	this->add(connection);
	return result;
}

string DatabaseManager::escape(string str)
{
	Connection *connection = this->get();

	while (true)
	{
		try
		{
			Query query = connection->query();

			query.escape_string(&str);
		}
		catch (const BadQuery &e)
		{
			switch (e.errnum())
			{
				case 1205:		// Lock wait timeout exceeded; try restarting transaction
				case 1213:		// Deadlock found when trying to get lock
					logger()->warning("Query escape finished with error %d, repeating", e.errnum());
					continue;
				case 2006:		// MySQL server has gone away
				case 2013:		// Lost connection to MySQL server during query
					logger()->debug("MySQL connection lost with error %d, repeating", e.errnum());
					this->connect(connection);
					continue;
			}
			logger()->warning("Failed to escape query %s, error %d", str.c_str(), e.errnum());
		}
		break;
	}

	this->add(connection);
	return str;
}