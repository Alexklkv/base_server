#include "Timers.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "EventListener.h"
#include "TimerEvent.h"
#include "TimersThread.h"

Timers::Timers(uint8_t num_threads):
	threads_count(num_threads), next_thread(0)
{
	this->threads = new TimersThread*[this->threads_count];

	for (uint8_t i = 0; i < this->threads_count; i++)
		this->threads[i] = new TimersThread();
}

Timers::~Timers()
{
	for (uint8_t i = 0; i < this->threads_count; i++)
		delete this->threads[i];

	delete [] this->threads;
}

void Timers::start_wait()
{
	for (uint8_t i = 0; i < this->threads_count; i++)
		this->threads[i]->start_wait();
}

void Timers::stop_wait()
{
	for (uint8_t i = 0; i < this->threads_count; i++)
		this->threads[i]->stop_wait();
}

void Timers::start(TimerEvent *timer)
{
	timer->thread->start(timer);
}

void Timers::stop(TimerEvent *timer)
{
	timer->thread->stop(timer);
}

void Timers::restart(TimerEvent *timer, double after, double repeat)
{
	timer->thread->restart(timer, after, repeat);
}

void Timers::remove(TimerEvent *timer)
{
	timer->thread->remove(timer);
}

TimerEvent* Timers::create(EventListener *listener, uint8_t type, double after, double repeat, uint32_t data)
{
	TimersThread *thread = this->threads[(++this->next_thread) % this->threads_count];
	return thread->create(listener, type, after, repeat, data);
}