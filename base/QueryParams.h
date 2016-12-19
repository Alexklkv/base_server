#pragma once

#include "NoCopy.h"
#include "QueryPair.h"

#include <vector>

class QueryParams : private NoCopy
{
private:
	std::vector<QueryPair*> pairs;

public:
	~QueryParams();

	QueryPair& operator[](const char *name);
	char* get_query(const char *secret);
};