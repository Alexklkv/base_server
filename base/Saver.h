#pragma once

#include "Thread.h"

#include <concurrent_queue.h>

class Savable;

class Saver : public Thread
{
private:
	typedef tbb::concurrent_queue<Savable*> objects_t;

	objects_t objects;

protected:
	void on_timeout();

public:
	Saver();
	~Saver();

	void add(Savable *object);
};