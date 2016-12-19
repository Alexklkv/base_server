#include "QueryPair.h"

#include "util.h"

#include <stdlib.h>
#include <string.h>

using std::string;

QueryPair::QueryPair(const char *name):
	name(name), value(nullptr)
{}

QueryPair::~QueryPair()
{
	if (this->value != nullptr)
		free(this->value);
}

QueryPair& QueryPair::operator=(const QueryPair &value)
{
	this->value = strdup(value.value);
	return *this;
}

QueryPair& QueryPair::operator=(const char *value)
{
	this->value = strdup(value);
	return *this;
}

QueryPair& QueryPair::operator=(uint64_t value)
{
	this->value = format("%lu", value);
	return *this;
}

QueryPair& QueryPair::operator=(uint32_t value)
{
	this->value = format("%u", value);
	return *this;
}

QueryPair& QueryPair::operator=(int64_t value)
{
	this->value = format("%ld", value);
	return *this;
}

QueryPair& QueryPair::operator=(int32_t value)
{
	this->value = format("%d", value);
	return *this;
}

bool QueryPair::operator<(const QueryPair &pair) const
{
	return (strcmp(this->name, pair.name) < 0);
}

string QueryPair::get_value() const
{
	return string(this->name) + "=" + this->value;
}

string QueryPair::get_escaped() const
{
	return escape(this->name) + "=" + escape(this->value);
}