#pragma once

#include "NoCopy.h"

#include <boost/interprocess/sync/interprocess_mutex.hpp>

namespace ev
{
	struct timer;
}

struct ev_loop;
class EventListener;
class TimersThread;

class TimerEvent : private NoCopy
{
	friend class Timers;
	friend class TimersThread;

private:
	typedef boost::interprocess::interprocess_mutex mutex_t;

	ev::timer *watcher;
	EventListener *listener;
	TimersThread *thread;

	uint8_t type;
	uint32_t data;

	double after;
	double repeat;

	bool stopped;
	bool removed;

	mutex_t mutex;

	TimerEvent(struct ev_loop *loop, TimersThread *thread);

	bool is_removed() const;

	void start();
	void stop();
	void remove();

	void on_timer(ev::timer &, int);

public:
	~TimerEvent();

	bool is_stopped() const;
};