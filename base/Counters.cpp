#include "Counters.h"

#include "BaseConfig.h"
#include "BaseDatabase.h"
#include "BaseServer.h"
#include "Log.h"

#include "util.h"

#include <time.h>

static const time_t COUNTERS_SAVE_TIMEOUT = 1 * 60;

Counters::Counters(time_t save_timeout, uint32_t max_counter):
	Thread("Counters", COUNTERS_SAVE_TIMEOUT), save_step(0), save_steps(save_timeout / COUNTERS_SAVE_TIMEOUT), max_type(max_counter)
{
	this->values = new counters_t[max_type];

	time_t curr_time = time(nullptr);
	tm now = localtime_threadsafe(curr_time);

	this->last_day = now.tm_yday;
}

Counters::~Counters()
{
	delete [] this->values;
}

int64_t Counters::get(CounterType type, const PackedFields &fields) const
{
	if (type >= this->max_type)
	{
		logger()->warning("Trying to get incorrect counter: %u", type);
		return 0;
	}

	const counters_t *counters = &(this->values[type]);

	auto iter = counters->find(fields.data);
	if (iter == counters->end())
		return 0;

	return iter->second.value;
}

void Counters::inc(CounterType type, const PackedFields &fields)
{
	this->change(type, fields.data, 1);
}

void Counters::dec(CounterType type, const PackedFields &fields)
{
	this->change(type, fields.data, -1);
}

void Counters::add(CounterType type, const PackedFields &fields, uint64_t value)
{
	this->change(type, fields.data, value);
}

void Counters::sub(CounterType type, const PackedFields &fields, uint64_t value)
{
	this->change(type, fields.data, -value);
}

void Counters::set(uint32_t type, uint64_t data, int64_t value)
{
	if (type >= this->max_type)
	{
		logger()->warning("Trying to set incorrect counter: %u", type);
		return;
	}

	Counter counter;
	counter.value = value;
	counter.changed = false;

	this->values[type].insert(std::make_pair(data, counter));
}

void Counters::change(CounterType type, uint64_t data, int64_t value)
{
	if (type >= this->max_type)
	{
		logger()->warning("Trying to change incorrect counter: %u", type);
		return;
	}

	Counter counter;
	counter.value = value;
	counter.changed = true;

	counters_t *counters = &(this->values[type]);

	auto result = counters->insert(std::make_pair(data, counter));
	if (result.second)
		return;

	Counter *exist = &(result.first->second);

	exist->value += value;
	exist->changed = true;
}

void Counters::load()
{
	base_database()->load_counters(this);
}

void Counters::save()
{
	time_t curr_time = time(nullptr);
	tm now = localtime_threadsafe(curr_time);

	if (this->last_day != now.tm_yday)
		this->clear_daily();
	this->last_day = now.tm_yday;

	base_database()->save_counters(this);
}

void Counters::clear_daily()
{
	for (uint32_t type = 0; type < this->max_type; type++)
	{
		if (!this->is_daily(type))
			continue;

		counters_t *counters = &(this->values[type]);
		for (auto iter = counters->begin(); iter != counters->end(); ++iter)
		{
			iter->second.value = 0;
			iter->second.changed = false;
		}
	}
}

bool Counters::is_daily(uint32_t type) const
{
	return config()->MINUTE_COUNTERS.find(type) == config()->MINUTE_COUNTERS.end();
}

void Counters::on_notify()
{
	this->save();
}

static bool day_change(const tm &now)
{
	return (now.tm_min == 0 || (now.tm_hour == 23 && now.tm_min == 59));
}

void Counters::on_timeout()
{
	time_t curr_time = time(nullptr);
	tm now = localtime_threadsafe(curr_time);

	if (day_change(now))
		this->save_step = this->save_steps;
	else
		this->save_step++;

	if (this->save_step != this->save_steps)
		return;

	this->save_step = 0;

	this->save();
}

void Counters::on_cleanup()
{
	this->save();
}