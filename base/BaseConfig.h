#pragma once

#include "Ban.h"

#include <string.h>

#include <unordered_set>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#define LOAD_STRING(name, default_value) strdup(this->secure_config.get<std::string>(name, default_value).c_str());

class BaseConfig
{
public:
	enum Protocol : uint8_t
	{
		PROTOCOL_TCP,
		PROTOCOL_UDP
	};

	const char *LOG_NAME;
	const char *LOCALE;
	uint32_t MAX_FILES_LIMIT;

	uint64_t API_VK_ID;
	char *API_VK_SECRET;
	uint32_t API_VK_DELAY;

	uint64_t API_MM_ID;
	char *API_MM_SECRET;

	char *API_OK_SECRET;
	char *API_OK_PUBLIC;

	char *API_FS_ID;
	char *API_FS_SECRET;

	uint64_t API_RG_ID;
	char *API_RG_SECRET;

	uint64_t API_FB_ID;
	char *API_FB_SECRET;

	char *API_ADMIN_SECRET;

	const char *API_URL_VK;
	const char *API_URL_MM;
	const char *API_URL_FS;
	const char *API_URL_OK;
	const char *API_URL_FB;

	const char *USERAGENT;

	const char *CROSSDOMAIN;
	uint32_t CROSSDOMAIN_LENGTH;

	uint16_t FS_TO_BALANCE;

	char *DATABASE_NAME;
	char *DATABASE_HOST;
	int DATABASE_PORT;
	char *DATABASE_USER;
	char *DATABASE_PASSWORD;
	uint32_t DATABASE_TIMEOUT;
	bool DATABASE_STATISTIC;

	const char *DEFAULT_IP;
	int BACKLOG;

	int TCP_SOCKET_KEEPALIVE;
	int TCP_SOCKET_NODELAY;

	uint16_t WRITER_INIT_SIZE;
	uint16_t UDP_BUFFER_SIZE;

	uint8_t CLIENTS_THREADS_COUNT;
	uint8_t TIMERS_THREADS_COUNT;

	uint16_t CLIENTS_IOS_CACHE;

	uint8_t BLOCKS_SAVE_SIZE;

	uint16_t SAVER_SAVE_TIMEOUT;
	uint16_t BAN_REPEAT_TIMEOUT;

	uint16_t PLAYER_EXPIRE_TIMEOUT;
	uint8_t PLAYER_MAX_BONUS;
	uint32_t PLAYER_CHEST_AMOUNT;

	uint8_t RATINGS_PAGE_PLACES;
	uint8_t RATINGS_TOP_PLACES;
	uint16_t RATINGS_UPDATE_TIMEOUT;

	uint8_t FLAGS_MAX_TYPE;
	uint8_t OFFERS_MAX_TYPE;
	uint8_t OFFER_NONE;

	const char *SECURE_CONFIG;
	const char *LOCATIONS_CONFIG;
	std::vector<BanTime> BAN_TIMES;

	boost::property_tree::ptree secure_config;

	struct Bind
	{
		char *ip;
		int port;

		Protocol protocol;
		bool web = false;
	};
	std::vector<Bind> BINDS;

	std::unordered_set<uint32_t> MINUTE_COUNTERS;

	BaseConfig()
	{
		this->LOG_NAME			= "daemon_%d%m%y_%H%M%S.log";
		this->LOCALE			= "ru_RU.UTF-8";
		this->MAX_FILES_LIMIT		= 16384;

		this->API_VK_ID			= 0;
		this->API_VK_SECRET		= nullptr;
		this->API_VK_DELAY		= 400000;

		this->API_MM_ID			= 0;
		this->API_MM_SECRET		= nullptr;

		this->API_OK_SECRET		= nullptr;
		this->API_OK_PUBLIC		= nullptr;

		this->API_FS_ID			= nullptr;
		this->API_FS_SECRET		= nullptr;

		this->API_RG_ID			= 0;
		this->API_RG_SECRET		= nullptr;

		this->API_FB_ID			= 0;
		this->API_FB_SECRET		= nullptr;

		this->API_ADMIN_SECRET		= nullptr;

		this->API_URL_VK		= "http://api.vk.com/api.php";
		this->API_URL_MM		= "http://www.appsmail.ru/platform/api";
		this->API_URL_FS		= "http://fotostrana.ru/apifs.php";
		this->API_URL_OK		= "http://api.odnoklassniki.ru/fb.do?method=";
		this->API_URL_FB		= "https://graph.facebook.com/";

		this->USERAGENT			= "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0";

		this->CROSSDOMAIN		=	"<?xml version=\"1.0\"?>"
							"<cross-domain-policy>"
								"<site-control permitted-cross-domain-policies=\"all\" />"
								"<allow-access-from domain=\"*\" to-ports=\"*\" />"
							"</cross-domain-policy>";

		this->CROSSDOMAIN_LENGTH	= strlen(this->CROSSDOMAIN) + 1;

		this->FS_TO_BALANCE		= 1;

		this->DATABASE_NAME		= nullptr;
		this->DATABASE_HOST		= nullptr;
		this->DATABASE_PORT		= 0;
		this->DATABASE_USER		= nullptr;
		this->DATABASE_PASSWORD		= nullptr;
		this->DATABASE_TIMEOUT		= 400000;
		this->DATABASE_STATISTIC	= false;

		this->DEFAULT_IP		= "";
		this->BINDS			= {};
		this->BACKLOG			= 128;
		this->WRITER_INIT_SIZE		= 256;
		this->UDP_BUFFER_SIZE		= 256;

		this->TCP_SOCKET_KEEPALIVE	= 1;
		this->TCP_SOCKET_NODELAY	= 0;

		this->CLIENTS_THREADS_COUNT	= 8;
		this->TIMERS_THREADS_COUNT	= 8;

		this->CLIENTS_IOS_CACHE		= 20000;

		this->BLOCKS_SAVE_SIZE		= 1;

		this->SAVER_SAVE_TIMEOUT	= 60;
		this->BAN_REPEAT_TIMEOUT	= 5 * 60;

		this->PLAYER_EXPIRE_TIMEOUT	= 60;
		this->PLAYER_MAX_BONUS		= 15;
		this->PLAYER_CHEST_AMOUNT	= 0;

		this->RATINGS_PAGE_PLACES	= 0;
		this->RATINGS_TOP_PLACES	= 0;
		this->RATINGS_UPDATE_TIMEOUT	= 60 * 60;

		this->FLAGS_MAX_TYPE		= 0;
		this->OFFERS_MAX_TYPE		= 0;
		this->OFFER_NONE		= 0;

		this->BAN_TIMES.push_back({static_cast<Ban::Type>(0), 0, static_cast<Ban::Type>(0), 0});
	}

	~BaseConfig()
	{
		free(this->DATABASE_NAME);
		free(this->DATABASE_HOST);
		free(this->DATABASE_USER);
		free(this->DATABASE_PASSWORD);

		free(this->API_VK_SECRET);
		free(this->API_MM_SECRET);
		free(this->API_OK_PUBLIC);
		free(this->API_OK_SECRET);
		free(this->API_FS_ID);
		free(this->API_FS_SECRET);
		free(this->API_RG_SECRET);
		free(this->API_FB_SECRET);

		free(this->API_ADMIN_SECRET);

		for (auto bind : this->BINDS)
			free(bind.ip);
	}
};