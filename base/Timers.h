#pragma once

#include "NoCopy.h"

class EventListener;
class TimerEvent;
class TimersThread;

class Timers : private NoCopy
{
private:
	TimersThread **threads;
	const uint8_t threads_count;
	uint8_t next_thread;

public:
	explicit Timers(uint8_t num_threads);
	virtual ~Timers();

	virtual void start_wait();
	virtual void stop_wait();

	virtual void start(TimerEvent *timer);
	virtual void stop(TimerEvent *timer);
	virtual void restart(TimerEvent *timer, double after = 0, double repeat = 0);

	virtual TimerEvent* create(EventListener *listener, uint8_t type, double after, double repeat = 0, uint32_t data = 0);
	virtual void remove(TimerEvent *timer);
};