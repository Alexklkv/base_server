#pragma once

#include <atomic.h>
#include <concurrent_unordered_map.h>

#include <string.h>

using tbb::atomic;

class QueryStatistic
{
private:
	struct Data
	{
		atomic<uint64_t> usecs;
		atomic<uint32_t> count;
	};

	typedef tbb::concurrent_unordered_map<std::string, Data> queries_t;

	queries_t queries;
	atomic<uint32_t> total;

	bool enabled;

public:
	QueryStatistic(bool enable);

	void print() const;

	void add(const char *query, int64_t usec);
};