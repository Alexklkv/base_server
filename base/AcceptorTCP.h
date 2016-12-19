#pragma once

#include "Acceptor.h"

class AcceptorTCP : public Acceptor
{
private:
	bool web;

	static void set_sock_options(int fd);
	static void on_connect(ev::io &w, int);

protected:
	void on_init();

public:
	AcceptorTCP(const char *ip, uint16_t port, bool web);
};