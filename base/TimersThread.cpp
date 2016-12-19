#include "TimersThread.h"

#include "TimerEvent.h"

TimersThread::TimersThread():
	Thread("Timers")
{}

void TimersThread::add(Action::Type type, TimerEvent *timer)
{
	Action action;
	action.type = type;
	action.timer = timer;
	this->actions.push(action);

	this->notify();
}

void TimersThread::on_notify()
{
	Action action;
	while (this->actions.try_pop(action))
	{
		switch (action.type)
		{
			case Action::TYPE_START:
				action.timer->start();
				break;
			case Action::TYPE_STOP:
				action.timer->stop();
				break;
			case Action::TYPE_REMOVE:
				delete action.timer;
				break;
		}
	}
}

TimerEvent* TimersThread::create(EventListener *listener, uint8_t type, double after, double repeat, uint32_t data)
{
	TimerEvent *timer = new TimerEvent(this->get_loop(), this);

	timer->listener = listener;
	timer->type = type;
	timer->after = after;
	timer->repeat = repeat;
	timer->data = data;

	return timer;
}

void TimersThread::start(TimerEvent *timer)
{
	this->add(Action::TYPE_START, timer);
}

void TimersThread::stop(TimerEvent *timer)
{
	this->add(Action::TYPE_STOP, timer);
}

void TimersThread::restart(TimerEvent *timer, double after, double repeat)
{
	timer->after = after;
	timer->repeat = repeat;

	this->add(Action::TYPE_START, timer);
}

void TimersThread::remove(TimerEvent *timer)
{
	timer->remove();
	this->add(Action::TYPE_REMOVE, timer);
}