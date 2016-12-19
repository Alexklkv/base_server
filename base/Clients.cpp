#include "Clients.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "ClientsThread.h"
#include "IO.h"
#include "Log.h"

#include "server/Packet.h"

#include <arpa/inet.h>
#include <sys/socket.h>

Clients::Clients():
	threads_count(config()->CLIENTS_THREADS_COUNT), next_thread(0)
{
	this->ios.reserve(config()->CLIENTS_IOS_CACHE);

	this->threads = new ClientsThread*[this->threads_count];

	for (size_t i = 0; i < this->threads_count; i++)
	{
		this->threads[i] = new ClientsThread;
		this->threads[i]->start_wait();
	}
}

Clients::~Clients()
{
	for (size_t i = 0; i < this->threads_count; i++)
		this->threads[i]->stop();

	for (auto iter : this->ios)
		iter->close();

	for (size_t i = 0; i < this->threads_count; i++)
		this->threads[i]->join();

	for (auto iter : this->ios)
		delete iter;

	for (size_t i = 0; i < this->threads_count; i++)
		delete this->threads[i];

	delete [] this->threads;
}

void Clients::connect_tcp(int socket, bool web, uint32_t ip)
{
	ClientsThread *thread = this->threads[(++this->next_thread) % this->threads_count];

	IO *io;
	if (!this->avail.try_pop(io))
	{
		io = new IO(config());
		BaseClient *client = BaseServer::instance()->create_client(io);
		io->client_pair(client);

		this->ios.push_back(io);
	}

	logger()->debug("Client connected from socket %d and assigned to IO %p at thread %p", socket, static_cast<void*>(io), static_cast<void*>(thread));

	udp_ios_t::accessor accessor;

	if (this->udp_ios.insert(accessor, socket))
		accessor->second = io;
	else
		logger()->warning("Socket %d already registered", socket);

	accessor.release();

	io->connect(web ? IO::Type::HTTP : IO::Type::BINARY, ip);
	thread->add(io, socket);
}

int Clients::connect_udp(uint32_t id, int socket, const sockaddr_in &addr)
{
	udp_ios_t::accessor accessor;

	if (this->udp_ios.find(accessor, id) && !accessor->second->tcp_stopped())
		return accessor->second->start_udp(socket);

	accessor.release();

	logger()->warning("Unknown client %u trying to connect to UDP from %s:%u", id, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	return 0;
}

void Clients::disconnect(IO *io, int socket)
{
	this->avail.push(io);

	if (!this->udp_ios.erase(socket))
		logger()->warning("Unexistent socket %u", socket);
}

void Clients::send(const server::Packet &packet)
{
	for (auto iter : this->ios)
		iter->send_tcp(packet);
}