#include "Acceptor.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Log.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <ev++.h>

Acceptor::Acceptor(const char *ip, uint16_t port, const char *name):
	Thread(name), ip(ip), port(port)
{}

int Acceptor::bind(const char *ip, uint16_t &port, int type)
{
	int socket_fd = socket(AF_INET, type, 0);
	if (socket_fd < 0)
	{
		logger()->warning("Failed to create socket type %u", type);
		return socket_fd;
	}

	int yes = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
	{
		logger()->warning("Failed to set option SO_REUSEADDR");
		return socket_fd;
	}

	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(ip);

	if (::bind(socket_fd, reinterpret_cast<const sockaddr*>(&sa), sizeof(sa)) < 0)
	{
		logger()->warning("Failed to bind server socket type %u to %s:%d", type, ip, port);
		return socket_fd;
	}

	if (port != 0)
		return socket_fd;

	socklen_t sa_len = sizeof(sa);
	getsockname(socket_fd, reinterpret_cast<sockaddr*>(&sa), &sa_len);
	port = ntohs(sa.sin_port);

	return socket_fd;
}

void Acceptor::on_cleanup()
{
	delete this->watcher;

	shutdown(this->socket_fd, SHUT_RDWR);
	close(this->socket_fd);
}

void Acceptor::on_stop()
{
	logger()->info("Stopping accept at %s:%d", this->ip, this->port);

	this->watcher->stop();
}

void Acceptor::on_init()
{
	logger()->info("Starting accept at %s:%d", this->ip, this->port);

	this->watcher = new ev::io(this->get_loop());
}