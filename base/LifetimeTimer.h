#pragma once

#include "NoCopy.h"
#include "TimerEvent.h"

class Timers;

class LifetimeTimer
{
	TimerEvent *timer;
	Timers *timers_manager;

	void remove();

public:
	LifetimeTimer(Timers *timers);
	virtual ~LifetimeTimer();

	void create(EventListener *listener, uint8_t event, double after, double repeat = 0.0, uint32_t data = 0);
	void start();
	void restart(double after, double repeat = 0.0);
	void stop();
};