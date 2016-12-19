#pragma once

#include "NoCopy.h"

#include <boost/property_tree/ptree.hpp>

#include <vector>

#include <ev++.h>

class Acceptor;
class Api;
class BaseClient;
class BaseConfig;
class BaseDatabase;
class Blocks;
class Clients;
class Counters;
class IO;
class Players;
class Saver;

class BaseServer : private NoCopy
{
private:
	static BaseServer *server;

	std::vector<Acceptor*> acceptors;

	static void on_shutdown(ev::sig &w, int);
	static void on_usersignal(ev::sig &, int);

	void delete_acceptors();

	virtual void shutdown_message() = 0;

protected:
	BaseServer(const BaseConfig *config, BaseDatabase *database, bool daemon_mode = false);
	virtual ~BaseServer();

	virtual void create_objects();
	virtual void destroy_objects();

	virtual void init_objects();
	virtual void finalize_objects();

public:
	const BaseConfig *config;
	boost::property_tree::ptree locations_config;

	Api *api;
	Clients *clients;
	Blocks *blocks;
	Counters *counters;
	BaseDatabase *database;
	Players *players;
	Saver *saver;

	static BaseServer* instance();

	void run();

	virtual BaseClient* create_client(IO *io) const = 0;
};

inline Api* api()
{
	return BaseServer::instance()->api;
}

inline const BaseConfig* config()
{
	return BaseServer::instance()->config;
}

inline const boost::property_tree::ptree locations_config()
{
	return BaseServer::instance()->locations_config;
}

inline Blocks* blocks()
{
	return BaseServer::instance()->blocks;
}

inline Clients* clients()
{
	return BaseServer::instance()->clients;
}

inline BaseDatabase* base_database()
{
	return BaseServer::instance()->database;
}

inline Players* players()
{
	return BaseServer::instance()->players;
}

inline Saver* saver()
{
	return BaseServer::instance()->saver;
}