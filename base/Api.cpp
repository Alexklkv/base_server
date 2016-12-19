#include "Api.h"

#include "ApiAchieve.h"
#include "ApiBalance.h"
#include "ApiQuery.h"
#include "BaseConfig.h"
#include "BasePlayer.h"
#include "BaseServer.h"
#include "Log.h"
#include "QueryParams.h"

#include "util.h"

#include <vector>

#include <stdlib.h>
#include <string.h>

#define API_FORMAT	"xml"

using std::string;

string Api::fb_token;

static size_t on_read_fb(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t length = size * nmemb;
	if (length == 0)
		return 0;

	std::vector<char> *buffer = static_cast<std::vector<char>*>(stream);

	size_t cur_size = buffer->size() - 1;
	buffer->resize(cur_size + length + 1, 0);

	memcpy(buffer->data() + cur_size, ptr, length);

	return length;
}

Api::Api()
{
	this->balance_db = new ApiBalance(ApiBalance::TYPE_DB);
	this->balance_db->start_wait();

	this->balance_fs = new ApiBalance(ApiBalance::TYPE_FS);
	this->balance_fs->start_wait();

	this->achieve_fs = new ApiAchieve;
	this->achieve_fs->start_wait();
}

Api::~Api()
{
	this->balance_fs->stop_wait();
	delete this->balance_fs;

	this->balance_db->stop_wait();
	delete this->balance_db;

	this->achieve_fs->stop_wait();
	delete this->achieve_fs;
}

void Api::init()
{
	if (config()->API_FB_ID != 0)
		init_fb_token();
}

bool Api::valid(Type type)
{
	switch (type)
	{
		case TYPE_VK:
		case TYPE_MM:
		case TYPE_OK:
		case TYPE_FB:
		case TYPE_RG:
		case TYPE_FS:
		case TYPE_BOT:
		case TYPE_ADMIN:
			return true;
	}

	return false;
}

void Api::refill_balance(BasePlayer *player)
{
	switch (player->type)
	{
		case TYPE_VK:
		case TYPE_MM:
		case TYPE_OK:
		case TYPE_FB:
		case TYPE_RG:
			this->balance_db->refill(player);
			break;
		case TYPE_FS:
			this->balance_fs->refill(player);
			break;
		case TYPE_BOT:
		case TYPE_ADMIN:
			return;
	}
}

bool Api::check_auth(Type type, uint64_t net_id, const char *auth_key, const char *session_key)
{
	char *buffer = nullptr;

	switch (type)
	{
		case TYPE_VK:
			buffer = format("%lu_%lu_%s", config()->API_VK_ID, net_id, config()->API_VK_SECRET);
			break;
		case TYPE_MM:
			buffer = format("%lu_%lu_%s", config()->API_MM_ID, net_id, config()->API_MM_SECRET);
			break;
		case TYPE_OK:
			if (session_key == nullptr)
				return false;

			buffer = format("%lu%s%s", net_id, session_key, config()->API_OK_SECRET);
			break;
		case TYPE_FB:
			buffer = format("%" PRIu64 "_%" PRIu64 "_%s", config()->API_FB_ID, net_id, config()->API_FB_SECRET);
			break;
		case TYPE_FS:
			buffer = format("%s_%lu_%s", config()->API_FS_ID, net_id, config()->API_FS_SECRET);
			break;
		case TYPE_RG:
			buffer = format("%lu_%lu_%s", config()->API_RG_ID, net_id, config()->API_RG_SECRET);
			break;
		case TYPE_BOT:
			return false;
		case TYPE_ADMIN:
			buffer = format("%lu_%s", net_id, config()->API_ADMIN_SECRET);
			break;
	}

	if (buffer == nullptr)
		return false;

	char *digest;
	digest = md5_get(buffer);

	size_t result = strcmp(auth_key, digest);

	free(digest);
	free(buffer);

	if (result != 0)
	{
		logger()->warning("Failed to authorize player %lu", net_id);
		return false;
	}

	return true;
}

void Api::set_achieve(BasePlayer *player, uint16_t achieve_id)
{
	this->achieve_fs->set(player, achieve_id);
}

void Api::init_fb_token()
{
	if (!fb_token.empty())
		return;

	std::vector<char> buffer;
	buffer.push_back(0);

	CURL *curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_USERAGENT, config()->USERAGENT);
	curl_easy_setopt(curl, CURLOPT_ENCODING, "");
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
	curl_easy_setopt(curl, CURLOPT_RANGE, nullptr);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 120);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120);
	curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 1);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, on_read_fb);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

	QueryParams params;

	params["client_secret"] = config()->API_FB_SECRET;
	params["grant_type"] = "client_credentials";
	params["client_id"] = config()->API_FB_ID;
	params["method"] = "post";

	char *post = params.get_query(config()->API_FB_SECRET);

	std::stringstream fb_url;
	fb_url << config()->API_URL_FB << "oauth/access_token";

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
	curl_easy_setopt(curl, CURLOPT_URL, fb_url.str().c_str());

	CURLcode res = curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	free(post);

	if (res != CURLE_OK)
	{
		logger()->warning("Failed to perform API FB query with result (%d): %s", res, curl_easy_strerror(res));
		return;
	}

	fb_token = buffer.data();
	if (fb_token.find("error") != string::npos)
	{
		logger()->warning("Failed to get FB token: %s", fb_token.c_str());
		fb_token.clear();
		return;
	}

	size_t pos = fb_token.find("=");
	fb_token = fb_token.substr(pos + 1, fb_token.size() - pos);
}

string Api::get_fb_url(uint64_t target_id)
{
	std::stringstream stream;
	stream << config()->API_URL_FB << target_id << "/apprequests";
	return stream.str();
}

bool Api::execute(CURL *curl, ApiQuery *query, const char *method, QueryParams &params)
{
	const char *secret = nullptr;

	params["method"] = method;

	switch (query->type)
	{
		case TYPE_VK:
			curl_easy_setopt(curl, CURLOPT_URL, config()->API_URL_VK);

			params["api_id"] = config()->API_VK_ID;
			params["format"] = API_FORMAT;
			params["random"] = static_cast<uint32_t>(random());
			params["timestamp"] = static_cast<uint32_t>(time(nullptr));
			params["v"] = "2.0";

			secret = config()->API_VK_SECRET;
			break;
		case TYPE_MM:
			curl_easy_setopt(curl, CURLOPT_URL, config()->API_URL_MM);

			params["app_id"] = config()->API_MM_ID;
			params["format"] = API_FORMAT;
			params["secure"] = 1;

			if (query->net_id != 0)
				params["uid"] = query->net_id;

			secret = config()->API_MM_SECRET;
			break;
		case TYPE_OK:
		{
			string ok_url = config()->API_URL_OK;
			ok_url += method;

			curl_easy_setopt(curl, CURLOPT_URL, ok_url.c_str());

			params["application_key"] = config()->API_OK_PUBLIC;
			params["format"] = API_FORMAT;

			secret = config()->API_OK_SECRET;
			break;
		}
		case TYPE_FS:
			curl_easy_setopt(curl, CURLOPT_URL, config()->API_URL_FS);

			params["appId"] = config()->API_FS_ID;
			params["format"] = 2;
			params["rand"] = static_cast<uint32_t>(random());
			params["timestamp"] = static_cast<uint32_t>(time(nullptr));

			secret = config()->API_FS_SECRET;
			break;
		case TYPE_FB:
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt (curl, CURLOPT_SSL_VERIFYHOST, 0);
			curl_easy_setopt(curl, CURLOPT_URL, get_fb_url(query->net_id).c_str());

			params["access_token"] = fb_token.c_str();

			secret = config()->API_FB_SECRET;
			break;
		case TYPE_RG:
		case TYPE_BOT:
		case TYPE_ADMIN:
			return false;
	}

	char *post = params.get_query(secret);

	curl_easy_setopt(curl, CURLOPT_USERAGENT, config()->USERAGENT);
	curl_easy_setopt(curl, CURLOPT_ENCODING, "");
	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
	curl_easy_setopt(curl, CURLOPT_RANGE, nullptr);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 120);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 120);
	curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 1);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);

	CURLcode res = curl_easy_perform(curl);

	free(post);

	if (res != CURLE_OK)
	{
		logger()->warning("Failed to perform API %u query with res (%d): %s", query->type, res, curl_easy_strerror(res));
		return false;
	}

	return true;
}