#pragma once

#include "Acceptor.h"

class AcceptorUDP : public Acceptor
{
private:
	static void set_sock_options(int fd);
	static void on_connect(ev::io &w, int);

protected:
	void on_init();

public:
	AcceptorUDP(const char *ip, uint16_t port);
};