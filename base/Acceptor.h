#pragma once

#include "Thread.h"

namespace ev
{
	struct io;
}

class Acceptor : public Thread
{
protected:
	ev::io *watcher;

	const char *ip;
	uint16_t port;
	int socket_fd;

	static int bind(const char *ip, uint16_t &port, int type);

	void on_cleanup();
	void on_stop();

	virtual void on_init();

public:
	Acceptor(const char *ip, uint16_t port, const char *name);
};