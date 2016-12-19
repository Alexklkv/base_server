#include "TimerEvent.h"

#include "EventListener.h"
#include "TimersThread.h"

#include <boost/interprocess/sync/scoped_lock.hpp>

#include <ev++.h>

using boost::interprocess::scoped_lock;

TimerEvent::TimerEvent(struct ev_loop *loop, TimersThread *thread):
	listener(nullptr), thread(thread), type(0), after(0), repeat(0), stopped(true), removed(false)
{
	this->watcher = new ev::timer(loop);
	this->watcher->set<TimerEvent, &TimerEvent::on_timer>(this);
}

TimerEvent::~TimerEvent()
{
	delete this->watcher;
}

void TimerEvent::start()
{
	if (this->is_removed())
		return;

	this->stopped = false;
	this->watcher->start(this->after, this->repeat);
}

void TimerEvent::stop()
{
	if (this->is_removed())
		return;

	this->stopped = true;
	this->watcher->stop();
}

void TimerEvent::remove()
{
	scoped_lock<mutex_t> lock(this->mutex);

	this->removed = true;
	this->listener = nullptr;
}

bool TimerEvent::is_stopped() const
{
	return this->stopped;
}

bool TimerEvent::is_removed() const
{
	return this->removed;
}

void TimerEvent::on_timer(ev::timer &, int)
{
	scoped_lock<mutex_t> lock(this->mutex, boost::interprocess::defer_lock);

	if (!lock.try_lock())
		return;

	if (this->is_removed() || this->is_stopped())
		return;

	this->listener->event(this->type, 0, this->data);
}