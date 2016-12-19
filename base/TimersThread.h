#pragma once

#include "Thread.h"

#include <concurrent_queue.h>

class EventListener;
class TimerEvent;

class TimersThread : public Thread
{
private:
	struct Action
	{
		enum Type : uint8_t
		{
			TYPE_START,
			TYPE_STOP,
			TYPE_REMOVE
		};

		Type type;
		TimerEvent *timer;

		Action():
			type(TYPE_START), timer(nullptr)
		{}
	};

	typedef tbb::concurrent_queue<Action> actions_t;

	actions_t actions;

	void add(Action::Type type, TimerEvent *timer);

protected:
	void on_notify();

public:
	TimersThread();

	void start(TimerEvent *timer);
	void stop(TimerEvent *timer);
	void restart(TimerEvent *timer, double after = 0, double repeat = 0);

	TimerEvent* create(EventListener *listener, uint8_t type, double after, double repeat = 0, uint32_t data = 0);
	void remove(TimerEvent *timer);
};