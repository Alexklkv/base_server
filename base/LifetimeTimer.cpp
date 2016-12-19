#include "LifetimeTimer.h"

#include "Timers.h"

LifetimeTimer::LifetimeTimer(Timers *timers):
	timer(nullptr), timers_manager(timers)
{}

LifetimeTimer::~LifetimeTimer()
{
	this->remove();
}

void LifetimeTimer::create(EventListener* listener, uint8_t event, double after, double repeat, uint32_t data)
{
	this->timer = this->timers_manager->create(listener, event, after, repeat, data);
}

void LifetimeTimer::remove()
{
	if (this->timer != nullptr)
	{
		this->timers_manager->remove(this->timer);
		this->timer = nullptr;
	}
}

void LifetimeTimer::start()
{
	if (this->timer != nullptr)
		this->timers_manager->start(this->timer);
}

void LifetimeTimer::restart(double after, double repeat)
{
	if (this->timer != nullptr)
		this->timers_manager->restart(this->timer, after, repeat);
}

void LifetimeTimer::stop()
{
	if (this->timer != nullptr)
		this->timers_manager->stop(this->timer);
}