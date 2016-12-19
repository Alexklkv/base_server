#pragma once

#include <atomic.h>

using tbb::atomic;

class Savable
{
protected:
	atomic<int> saved;
	time_t saved_time;

public:
	static const int SAVED_NONE	= 0x00;
	static const int SAVED_DATA	= 0x01;
	static const int SAVED_INFO	= 0x02;
	static const int SAVED_OTHER	= 0x04;
	static const int SAVED_ALL	= 0x07;

	uint32_t inner_id;

	explicit Savable(uint32_t inner_id);
	virtual ~Savable();

	virtual void saved_remove(int what);

	virtual bool is_expired() const = 0;
	virtual bool save() = 0;
};