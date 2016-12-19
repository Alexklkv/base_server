#pragma once

#include "NoCopy.h"

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include <pthread.h>

namespace ev
{
	struct dynamic_loop;
	struct async;
	struct timer;
}

struct ev_loop;

class Thread : private NoCopy
{
	friend void* working_thread(void *arg);

private:
	typedef boost::interprocess::interprocess_semaphore mutex_t;

	mutex_t mutex;

	const char *name;
	int timeout;

	ev::dynamic_loop *loop;
	ev::async *notifier;
	ev::timer *timer;
	pthread_t thread_id;

	bool stopped;
	bool finished;

	void on_notify_p(ev::async &w, int revents);
	void on_timeout_p(ev::timer &w, int revents);

	void start();

protected:
	virtual void notify();

	virtual void on_init() {}
	virtual void on_run() {}
	virtual void on_cleanup() {}
	virtual void on_stop() {}

	virtual void on_notify() {}
	virtual void on_timeout() {}

	ev_loop* get_loop() const;

	bool is_stopped() const;

public:
	Thread(const char *name, int timeout = 0);
	virtual ~Thread();

	void stop();
	void join();

	void start_wait();
	void stop_wait();
};