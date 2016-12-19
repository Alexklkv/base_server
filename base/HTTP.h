#pragma once

#include <map>
#include <string>

using std::string;

class HTTP
{
public:
	enum class Method : uint8_t
	{
		GET = 0,
		POST,
		HEAD,
		PUT,
		DELETE,
		TRACE,
		CONNECT,

		MAX_METHOD
	};

	enum class Version : uint8_t
	{
		HTTP_1_0 = 0,
		HTTP_1_1,

		MAX_VERSION
	};

	enum class Field : uint8_t
	{
		// HTTP 1.1
		ACCEPT = 0,
		ACCEPT_CHARSET,
		ACCEPT_ENCODING,
		ACCEPT_LANGUAGE,
		ACCEPT_RANGES,
		AGE,
		ALLOW,
		AUTHORIZATION,
		CACHE_CONTROL,
		CONNECTION,
		CONTENT_ENCODING,
		CONTENT_LANGUAGE,
		CONTENT_LENGTH,
		CONTENT_LOCATION,
		CONTENT_MD5,
		CONTENT_RANGE,
		CONTENT_TYPE,
		DATE,
		ETAG,
		EXPECT,
		EXPIRES,
		FROM,
		HOST,
		IF_MATCH,
		IF_MODIFIED_SINCE,
		IF_NONE_MATCH,
		IF_RANGE,
		IF_UNMODIFIED_SINCE,
		LAST_MODIFIED,
		LOCATION,
		MAX_FORWARDS,
		PRAGMA,
		PROXY_AUTHENTICATE,
		PROXY_AUTHORIZATION,
		RANGE,
		REFERER,
		RETRY_AFTER,
		SERVER,
		TE,
		TRAILER,
		TRANSFER_ENCODING,
		UPGRADE,
		USER_AGENT,
		VARY,
		VIA,
		WARNING,
		WWW_AUTHENTICATE,

		// WebSocket
		ORIGIN,
		SEC_WEBSOCKET_KEY,
		SEC_WEBSOCKET_EXTENSIONS,
		SEC_WEBSOCKET_ACCEPT,
		SEC_WEBSOCKET_PROTOCOL,
		SEC_WEBSOCKET_VERSION,

		MAX_FIELD
	};

private:
	typedef std::multimap<Field, string> header_t;

public:
	Method method;
	string url;
	Version version;
	header_t header;

	bool valid;
	char *data;

	HTTP();
	~HTTP();

	const char* get(Field field) const;
	bool has(Field field, const char *compare = nullptr) const;

	bool parse(char *buffer, uint32_t &length);
};