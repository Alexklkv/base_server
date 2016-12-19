#include "BaseServer.h"

#include "AcceptorTCP.h"
#include "AcceptorUDP.h"
#include "Api.h"
#include "BaseConfig.h"
#include "Blocks.h"
#include "Clients.h"
#include "Counters.h"
#include "Exception.h"
#include "Log.h"
#include "Players.h"
#include "Saver.h"

#include <sstream>

#include <arpa/inet.h>
#include <boost/property_tree/json_parser.hpp>
#include <libxml/parser.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/resource.h>
#include <sys/socket.h>

#include <errno.h>
#include <fcntl.h>
#include <time.h>

BaseServer *BaseServer::server = nullptr;

BaseServer *BaseServer::instance()
{
	if (BaseServer::server == nullptr)
		throw Exception("Server is not created");

	return BaseServer::server;
}

void BaseServer::on_shutdown(ev::sig &w, int)
{
	w.loop.break_loop(ev::ALL);
}

void BaseServer::on_usersignal(ev::sig&, int)
{
	BaseServer::instance()->shutdown_message();
	BaseServer::instance()->delete_acceptors();
}

void BaseServer::delete_acceptors()
{
	while (!this->acceptors.empty())
	{
		Acceptor *acceptor = this->acceptors.back();
		this->acceptors.pop_back();

		acceptor->stop_wait();
		delete acceptor;
	}
}

BaseServer::BaseServer(const BaseConfig *config, BaseDatabase *database, bool daemon_mode)
{
	if (BaseServer::server != nullptr)
		throw Exception("Server already created");
	BaseServer::server = this;

	if (config == nullptr || database == nullptr)
		throw Exception("Incorrect server construction");

	this->config = config;
	this->database = database;

	boost::property_tree::json_parser::read_json(config->LOCATIONS_CONFIG, this->locations_config);

	xmlInitParser();
	LIBXML_TEST_VERSION

	setlocale(LC_CTYPE, config->LOCALE);

	srandom(time(nullptr));

	if (daemon_mode)
	{
		if (daemon(1, 0) < 0)
			logger()->error("Can't fork to daemon mode");
	}

	logger()->info("Using libev %d.%d", ev::version_major(), ev::version_minor());

	if (!(ev::recommended_backends() & EVBACKEND_EPOLL))
		logger()->error("System do not support epoll backend");

	struct rlimit rlim;
	rlim.rlim_cur = config->MAX_FILES_LIMIT;
	rlim.rlim_max = config->MAX_FILES_LIMIT;
	setrlimit(RLIMIT_NOFILE, &rlim);
	getrlimit(RLIMIT_NOFILE, &rlim);

	logger()->debug("Max files limit is %lu:%lu", rlim.rlim_cur, rlim.rlim_max);

	Api::init();
}

BaseServer::~BaseServer()
{
	xmlCleanupParser();

	BaseServer::server = nullptr;
}

void BaseServer::run()
{
	this->create_objects();
	this->init_objects();
	for (const auto &bind : this->config->BINDS)
	{
		Acceptor *acceptor;

		if (bind.protocol == BaseConfig::PROTOCOL_UDP)
			acceptor = new AcceptorUDP(bind.ip, bind.port);
		else if (bind.protocol == BaseConfig::PROTOCOL_TCP)
			acceptor = new AcceptorTCP(bind.ip, bind.port, bind.web);
		else
			continue;

		this->acceptors.push_back(acceptor);
		acceptor->start_wait();
	}

	ev::loop_ref loop = ev::get_default_loop();

	ev::sig signal_watcher_int(loop);
	signal_watcher_int.set<BaseServer::on_shutdown>();
	signal_watcher_int.start(SIGINT);

	ev::sig signal_watcher_term(loop);
	signal_watcher_term.set<BaseServer::on_shutdown>();
	signal_watcher_term.start(SIGTERM);

	ev::sig signal_watcher_usr(loop);
	signal_watcher_usr.set<BaseServer::on_usersignal>();
	signal_watcher_usr.start(SIGUSR1);

	loop.run(0);

	signal_watcher_usr.stop();
	signal_watcher_term.stop();
	signal_watcher_int.stop();

	this->delete_acceptors();
	this->finalize_objects();
	this->destroy_objects();

	logger()->info("Graceful exit");
}

void BaseServer::create_objects()
{
	this->players = new Players;
	this->api = new Api;
	this->saver = new Saver;
	this->blocks = new Blocks;
	this->clients = new Clients;
}

void BaseServer::destroy_objects()
{
	delete this->clients;
	delete this->blocks;
	delete this->saver;
	delete this->api;
	delete this->players;
}

void BaseServer::init_objects()
{
	this->saver->start_wait();
	this->blocks->start_wait();
}

void BaseServer::finalize_objects()
{
	this->blocks->stop_wait();
	this->saver->stop_wait();
}