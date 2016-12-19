#pragma once

#include "NoCopy.h"

#include <cstdint>
#include <string>

#include <curl/curl.h>

class ApiAchieve;
class ApiBalance;
class BaseConfig;
class BasePlayer;
class QueryParams;

struct ApiQuery;

class Api : private NoCopy
{
	friend class ApiAchieve;
	friend class ApiBalance;
	friend class ApiNotify;

public:
	enum Type : uint8_t
	{
		TYPE_VK = 0,
		TYPE_MM = 1,
		TYPE_OK = 4,
		TYPE_FB = 5,

		TYPE_FS = 30,
		TYPE_RG = 32,

		TYPE_BOT = 254,
		TYPE_ADMIN = 255
	};

private:

	ApiAchieve *achieve_fs;

	ApiBalance *balance_db;
	ApiBalance *balance_fs;

	static std::string fb_token;

	static void init_fb_token();
	static std::string get_fb_url(uint64_t target_id);

	static bool execute(CURL *curl, ApiQuery *query, const char *method, QueryParams &params);

public:
	Api();
	~Api();

	static void init();
	static bool valid(Type type);

	static bool check_auth(Type type, uint64_t net_id, const char *auth_key, const char *session_key);

	void refill_balance(BasePlayer *player);
	void set_achieve(BasePlayer *player, uint16_t achieve_id);
};