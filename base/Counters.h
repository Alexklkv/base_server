#pragma once

#include "Thread.h"
#include "PackedFields.h"

#include <atomic.h>
#include <concurrent_unordered_map.h>

class BaseDatabase;

enum CounterType : uint32_t;

using tbb::atomic;

class Counters : public Thread
{
	friend class BaseDatabase;

private:
	struct Counter
	{
		Counter(): changed(false) {this->value = 0;}

		atomic<int64_t> value;
		bool changed;
	};

	typedef tbb::concurrent_unordered_map<uint64_t, Counter> counters_t;

	counters_t *values;
	int save_step;
	int save_steps;
	int last_day;

	uint32_t max_type;

	void set(uint32_t type, uint64_t data, int64_t value);
	void change(CounterType type, uint64_t data, int64_t value);

	void clear_daily();

	bool is_daily(uint32_t type) const;

protected:
	void save();

	virtual void on_notify() override;
	virtual void on_timeout() override;
	virtual void on_cleanup() override;

public:
	Counters(time_t save_timeout, uint32_t max_counter);
	virtual ~Counters();

	virtual void load();

	virtual int64_t get(CounterType type, const PackedFields &fields = 0) const;

	virtual void inc(CounterType type, const PackedFields &fields = 0);
	virtual void dec(CounterType type, const PackedFields &fields = 0);

	virtual void add(CounterType type, const PackedFields &fields, uint64_t value);
	virtual void sub(CounterType type, const PackedFields &fields, uint64_t value);
};