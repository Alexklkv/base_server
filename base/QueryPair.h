#pragma once

#include <string>

class QueryPair
{
private:
	const char *name;
	char *value;

public:
	explicit QueryPair(const char *name);
	~QueryPair();

	QueryPair& operator=(const QueryPair &value);
	QueryPair& operator=(const char *value);
	QueryPair& operator=(uint64_t value);
	QueryPair& operator=(uint32_t value);
	QueryPair& operator=(int64_t value);
	QueryPair& operator=(int32_t value);

	bool operator<(const QueryPair &a) const;
	std::string get_value() const;
	std::string get_escaped() const;
};