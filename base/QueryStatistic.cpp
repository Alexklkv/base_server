#include "QueryStatistic.h"

#include "Log.h"

using std::string;

QueryStatistic::QueryStatistic(bool enable):
	enabled(enable)
{
	this->total = 0;
}

void QueryStatistic::add(const char *query, int64_t usec)
{
	if (!this->enabled)
		return;

	Data data;
	data.usecs = usec;
	data.count = 1;

	string query_copy(query);

	auto result = this->queries.insert(std::make_pair(query_copy, data));
	if (result.second)
		return;

	Data &old_data = result.first->second;

	old_data.usecs += usec;
	old_data.count += 1;

	if (++this->total % 100000 != 0)
		return;

	this->print();
}

void QueryStatistic::print() const
{
	for (auto iter = this->queries.begin(); iter != this->queries.end(); ++iter)
		logger()->info("%lu;%u;%s", iter->second.usecs.load(), iter->second.count.load(), iter->first.c_str());
}