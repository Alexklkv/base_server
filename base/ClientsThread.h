#pragma once

#include "Thread.h"

#include <concurrent_queue.h>

class IO;

class ClientsThread : public Thread
{
private:
	typedef tbb::concurrent_queue<IO*> added_t;

	added_t added;

protected:
	void on_notify();

public:
	ClientsThread();

	void add(IO *io, int socket);
};