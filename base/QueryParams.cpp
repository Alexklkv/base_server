#include "QueryParams.h"

#include "QueryPair.h"

#include "util.h"

#include <algorithm>
#include <string>

#include <string.h>

using std::sort;
using std::string;

static bool pairs_compare(const QueryPair *a, const QueryPair *b);

QueryParams::~QueryParams()
{
	for (auto iter : this->pairs)
		delete iter;
}

QueryPair& QueryParams::operator[](const char *name)
{
	QueryPair *pair = new QueryPair(name);

	this->pairs.push_back(pair);

	return *pair;
}

char* QueryParams::get_query(const char *secret)
{
	sort(this->pairs.begin(), this->pairs.end(), pairs_compare);

	string sig = "", query = "";

	for (auto iter : this->pairs)
	{
		sig += iter->get_value();

		query += iter->get_escaped();
		query += "&";
	}

	sig += secret;

	char *digest = md5_get(sig.c_str());

	query += "sig=";
	query += digest;

	free(digest);

	return strdup(query.c_str());
}

static bool pairs_compare(const QueryPair *a, const QueryPair *b)
{
	return *a < *b;
}