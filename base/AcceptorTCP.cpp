#include "AcceptorTCP.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Clients.h"
#include "Log.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <errno.h>
#include <fcntl.h>

void AcceptorTCP::set_sock_options(int fd)
{
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &config()->TCP_SOCKET_KEEPALIVE, sizeof(config()->TCP_SOCKET_KEEPALIVE)) < 0)
		logger()->error("Failed to set option SO_KEEPALIVE");

	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &config()->TCP_SOCKET_NODELAY, sizeof(config()->TCP_SOCKET_NODELAY)) < 0)
		logger()->error("Failed to set option TCP_NODELAY");

	int flags = fcntl(fd, F_GETFL);
	if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		logger()->error("Failed to set socket to nonblock mode");
}

void AcceptorTCP::on_connect(ev::io &w, int)
{
	while (true)
	{
		sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);

		logger()->debug("Trying to accept new TCP connection");

		int client_fd = accept(w.fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
		if (client_fd < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;

			logger()->warning("Failed to accept connection, errno %d", errno);
			return;
		}

		logger()->debug("Accepted new connection %d", client_fd);

		set_sock_options(client_fd);

		logger()->debug("Socket %d options set", client_fd);

		bool web = (w.data != nullptr);

		clients()->connect_tcp(client_fd, web, ntohl(client_addr.sin_addr.s_addr));

		logger()->debug("Socket %d added to manager", client_fd);
	}
}

AcceptorTCP::AcceptorTCP(const char *ip, uint16_t port, bool web):
	Acceptor(ip, port, "AcceptorTCP"), web(web)
{}

void AcceptorTCP::on_init()
{
	this->socket_fd = Acceptor::bind(this->ip, this->port, SOCK_STREAM);
	if (this->socket_fd < 0)
	{
		logger()->error("Failed bind on TCP ip: %s port: %u", this->ip, this->port);
		return;
	}

	if (listen(this->socket_fd, config()->BACKLOG) < 0)
	{
		logger()->warning("Failed to make server listen on TCP port %u", this->port);
		return;
	}

	set_sock_options(this->socket_fd);

	Acceptor::on_init();

	this->watcher->set<AcceptorTCP::on_connect>(this->web ? (void*) 1 : nullptr);
	this->watcher->start(this->socket_fd, ev::READ);
}