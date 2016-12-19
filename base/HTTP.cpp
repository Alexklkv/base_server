#include "HTTP.h"

#include "Log.h"

#include <boost/algorithm/string.hpp>

#include <string.h>

struct Comparator
{
	bool operator()(const char *a, const char *b) const
	{
		return (strcasecmp(a, b) < 0);
	}
};

static const std::map<const char*, HTTP::Method, Comparator> methods =
{
	{"GET", HTTP::Method::GET},
	{"POST", HTTP::Method::POST},
	{"HEAD", HTTP::Method::HEAD},
	{"PUT", HTTP::Method::PUT},
	{"DELETE", HTTP::Method::DELETE},
	{"TRACE", HTTP::Method::TRACE},
	{"CONNECT", HTTP::Method::CONNECT}
};

static const std::map<const char*, HTTP::Version, Comparator> versions =
{
	{"HTTP/1.0", HTTP::Version::HTTP_1_0},
	{"HTTP/1.1", HTTP::Version::HTTP_1_1}
};

static const std::map<const char*, HTTP::Field, Comparator> fields =
{
/*
	{"Accept", HTTP::Field::ACCEPT},
	{"Accept-Charset", HTTP::Field::ACCEPT_CHARSET},
	{"Accept-Encoding", HTTP::Field::ACCEPT_ENCODING},
	{"Accept-Language", HTTP::Field::ACCEPT_LANGUAGE},
	{"Accept-Ranges", HTTP::Field::ACCEPT_RANGES},
	{"Age", HTTP::Field::AGE},
	{"Allow", HTTP::Field::ALLOW},
	{"Authorization", HTTP::Field::AUTHORIZATION},
	{"Cache-Control", HTTP::Field::CACHE_CONTROL},
*/

	{"Connection", HTTP::Field::CONNECTION},

/*
	{"Content-Encoding", HTTP::Field::CONTENT_ENCODING},
	{"Content-Language", HTTP::Field::CONTENT_LANGUAGE},
	{"Content-Length", HTTP::Field::CONTENT_LENGTH},
	{"Content-Location", HTTP::Field::CONTENT_LOCATION},
	{"Content-MD5", HTTP::Field::CONTENT_MD5},
	{"Content-Range", HTTP::Field::CONTENT_RANGE},
	{"Content-Type", HTTP::Field::CONTENT_TYPE},
	{"Date", HTTP::Field::DATE},
	{"ETag", HTTP::Field::ETAG},
	{"Expect", HTTP::Field::EXPECT},
	{"Expires", HTTP::Field::EXPIRES},
	{"From", HTTP::Field::FROM},
	{"Host", HTTP::Field::HOST},
	{"IF-Match", HTTP::Field::IF_MATCH},
	{"IF-Modified-Since", HTTP::Field::IF_MODIFIED_SINCE},
	{"IF-None-Match", HTTP::Field::IF_NONE_MATCH},
	{"IF-Range", HTTP::Field::IF_RANGE},
	{"IF-Unmodified-Since", HTTP::Field::IF_UNMODIFIED_SINCE},
	{"Last-Modified", HTTP::Field::LAST_MODIFIED},
	{"Location", HTTP::Field::LOCATION},
	{"Max-Forwards", HTTP::Field::MAX_FORWARDS},
	{"Pragma", HTTP::Field::PRAGMA},
	{"Proxy-Authenticate", HTTP::Field::PROXY_AUTHENTICATE},
	{"Proxy-Authorization", HTTP::Field::PROXY_AUTHORIZATION},
	{"Range", HTTP::Field::RANGE},
	{"Referer", HTTP::Field::REFERER},
	{"Retry-After", HTTP::Field::RETRY_AFTER},
	{"Server", HTTP::Field::SERVER},
	{"TE", HTTP::Field::TE},
	{"Trailer", HTTP::Field::TRAILER},
	{"Transfer-Encoding", HTTP::Field::TRANSFER_ENCODING},
*/

	{"Upgrade", HTTP::Field::UPGRADE},

/*
	{"User-Agent", HTTP::Field::USER_AGENT},
	{"Vary", HTTP::Field::VARY},
	{"Via", HTTP::Field::VIA},
	{"Warning", HTTP::Field::WARNING},
	{"WWW-Authenticate", HTTP::Field::WWW_AUTHENTICATE},
*/

	// WebSocket
	{"Origin", HTTP::Field::ORIGIN},
	{"Sec-WebSocket-Key", HTTP::Field::SEC_WEBSOCKET_KEY},
	{"Sec-WebSocket-Extensions", HTTP::Field::SEC_WEBSOCKET_EXTENSIONS},
	{"Sec-WebSocket-Accept", HTTP::Field::SEC_WEBSOCKET_ACCEPT},
	{"Sec-WebSocket-Protocol", HTTP::Field::SEC_WEBSOCKET_PROTOCOL},
	{"Sec-WebSocket-Version", HTTP::Field::SEC_WEBSOCKET_VERSION}
};

HTTP::HTTP():
	method(Method::MAX_METHOD), version(Version::MAX_VERSION),
	valid(false), data(nullptr)
{}

HTTP::~HTTP()
{
	free(this->data);
}

bool HTTP::parse(char *buffer, uint32_t &length)
{
	const char *end = strstr(buffer, "\r\n\r\n");
	if (end == nullptr)
		return false;

	this->data = strdup(buffer);

	enum class Token
	{
		METHOD = 0,
		URL,
		VERSION,
		FIELD_NAME,
		FIELD_VALUE
	};

	Token next = Token::METHOD;
	Field field = Field:: MAX_FIELD;

	char *current = buffer;
	char *last = buffer;

	while (*current != '\0')
	{
		char sym = *current;

		if (sym == ' ')
		{
			if (next == Token::FIELD_VALUE)
			{
				++current;
				continue;
			}

			*current = '\0';

			switch (next)
			{
				case Token::METHOD:
				{
					auto iter = methods.find(last);
					if (iter == methods.end())
						return true;

					this->method = iter->second;
					next = Token::URL;
					break;
				}
				case Token::URL:
				{
					if (*last != '/')
						return true;

					this->url.assign(last);
					next = Token::VERSION;
					break;
				}
				default:
					// Skip ending spaces??
					return true;
			}

			++current;
		}
		else if (sym == '\r')
		{
			if (current[1] != '\n')
				return true;

			*current = '\0';

			switch (next)
			{
				case Token::VERSION:
				{
					auto iter = versions.find(last);
					if (iter == versions.end())
						return true;

					this->version = iter->second;
					next = Token::FIELD_NAME;
					break;
				}
				case Token::FIELD_VALUE:
				{
					if (field != Field::MAX_FIELD)
						this->header.insert(std::make_pair(field, string(last)));

					next = Token::FIELD_NAME;
					break;
				}
				default:
					return true;
			}

			++current;
			++current;

			if (current[0] == '\r' && current[1] == '\n')
			{
				length = current - buffer + 2;
				this->valid = true;
				return true;
			}
		}
		else if (sym == ':')
		{
			if (next != Token::FIELD_NAME)
			{
				++current;
				continue;
			}

			*current = '\0';

			auto iter = fields.find(last);
			if (iter == fields.end())
				field = Field::MAX_FIELD;
			else
				field = iter->second;

			next = Token::FIELD_VALUE;

			++current;
		}
		else if (sym == '\n')
			return true;
		else
		{
			++current;
			continue;
		}

		last = current;
		while (*last == ' ')
			++last;

		current = last + 1;
	}

	return true;
}

const char* HTTP::get(Field field) const
{
	auto iter = this->header.find(field);
	if (iter == this->header.end())
		return nullptr;

	return iter->second.c_str();
}

bool HTTP::has(Field field, const char *compare) const
{
	const char *value = this->get(field);
	if (value == nullptr)
		return false;

	if (compare == nullptr)
		return true;

	return strcasestr(value, compare);
}