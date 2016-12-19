#include "Thread.h"

#include "BaseServer.h"
#include "Log.h"

#include <ev++.h>

void* working_thread(void *arg)
{
	Thread *thread = static_cast<Thread*>(arg);

	thread->start();

	return nullptr;
}

Thread::Thread(const char *name, int timeout):
	mutex(0), name(name), timeout(timeout), loop(nullptr), notifier(nullptr), timer(nullptr), thread_id(0), stopped(false), finished(false)
{}

Thread::~Thread()
{
	if (this->finished || this->loop == nullptr)
		return;

	logger()->warning("%s thread %lx is running and being deleted!", this->name, pthread_self());

	this->stop_wait();
}

struct ev_loop* Thread::get_loop() const
{
	return *this->loop;
}

bool Thread::is_stopped() const
{
	return this->stopped;
}

void Thread::start_wait()
{
	if (this->loop != nullptr)
	{
		logger()->warning("Thread %s is arleady created", this->name);
		return;
	}

	if (pthread_create(&this->thread_id, nullptr, working_thread, this) != 0)
		logger()->error("Failed to start %s thread", this->name);

	this->mutex.wait();
}

void Thread::start()
{
	logger()->info("%s thread %lx is started", this->name, pthread_self());

	this->loop = new ev::dynamic_loop(ev::AUTO);

	this->notifier = new ev::async(*this->loop);
	this->notifier->set<Thread, &Thread::on_notify_p>(this);
	this->notifier->start();

	if (this->timeout != 0)
	{
		this->timer = new ev::timer(*this->loop);
		this->timer->set<Thread, &Thread::on_timeout_p>(this);
		this->timer->start(this->timeout, this->timeout);
	}

	this->on_init();

	this->mutex.post();

	this->on_run();

	this->loop->run(0);

	this->on_cleanup();

	delete this->notifier;
	delete this->loop;

	if (this->timer != nullptr)
		delete this->timer;

	logger()->info("%s thread %lx is stopped", this->name, pthread_self());
}

void Thread::stop()
{
	if (this->stopped)
		return;

	this->stopped = true;
	this->notifier->send();
}

void Thread::join()
{
	if (this->thread_id == 0)
		return;

	pthread_join(this->thread_id, nullptr);
	this->thread_id = 0;
	this->finished = true;
}

void Thread::stop_wait()
{
	if (this->thread_id == 0)
	{
		logger()->warning("Thread %s is requested to stop but was not created!", this->name);
		return;
	}

	this->stop();
	this->join();
}

void Thread::notify()
{
	this->notifier->send();
}

void Thread::on_notify_p(ev::async &, int)
{
	//logger()->debug("%s thread %lx notified", this->name, pthread_self());

	if (!this->stopped)
	{
		this->on_notify();
		return;
	}

	this->on_stop();

	if (this->timer != nullptr)
		this->timer->stop();
	this->notifier->stop();
}

void Thread::on_timeout_p(ev::timer &, int)
{
	logger()->debug("%s thread timed out", this->name);

	this->on_timeout();
}