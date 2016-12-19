#include "AcceptorUDP.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Clients.h"
#include "Log.h"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <fcntl.h>

void AcceptorUDP::set_sock_options(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		logger()->error("Failed to set socket to nonblock mode");
}

void AcceptorUDP::on_connect(ev::io &w, int)
{
	while (true)
	{
		uint32_t client_id;
		sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);

		int size = recvfrom(w.fd, &client_id, sizeof(client_id), 0, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
		if (size < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			return;

		if (size < 0)
		{
			logger()->warning("Acceptor UDP socket %d error %d", w.fd, errno);
			return;
		}

		if (size != sizeof(client_id))
		{
			logger()->warning("Acceptor UDP packet size %d from %s:%u", size, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			return;
		}

		logger()->debug("Trying to accept new UDP connection");

		sockaddr_in sa;
		socklen_t sa_len = sizeof(sa);
		getsockname(w.fd, reinterpret_cast<sockaddr*>(&sa), &sa_len);
		uint16_t port = ntohs(sa.sin_port);

		int tmp_fd = Acceptor::bind(config()->DEFAULT_IP, port, SOCK_DGRAM);
		if (tmp_fd < 0)
			return;

		set_sock_options(tmp_fd);

		int client_fd = clients()->connect_udp(client_id, tmp_fd, client_addr);
		if (client_fd != tmp_fd)
		{
			if (close(tmp_fd) < 0)
				logger()->warning("Failed to close temporary UDP socket %d error %d", tmp_fd, errno);

			if (client_fd == 0)
				return;
		}

		if (connect(client_fd, reinterpret_cast<const sockaddr*>(&client_addr), client_len) < 0)
		{
			logger()->warning("Failed to connect UDP socket %d error %d", client_fd, errno);
			return;
		}

		send(client_fd, nullptr, 0, 0);
	}
}

AcceptorUDP::AcceptorUDP(const char *ip, uint16_t port):
	Acceptor(ip, port, "AcceptorUDP")
{}

void AcceptorUDP::on_init()
{
	this->socket_fd = Acceptor::bind(this->ip, this->port, SOCK_DGRAM);
	if (this->socket_fd < 0)
		return;

	set_sock_options(this->socket_fd);

	Acceptor::on_init();

	this->watcher->set<AcceptorUDP::on_connect>(&this->port);
	this->watcher->start(this->socket_fd, ev::READ);
}