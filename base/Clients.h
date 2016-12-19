#pragma once

#include "NoCopy.h"

#include "server/Packet.h"

#include <netinet/in.h>

#include <concurrent_hash_map.h>
#include <concurrent_queue.h>
#include <concurrent_vector.h>

class ClientsThread;
class IO;

class Clients : private NoCopy
{
private:
	typedef tbb::concurrent_hash_map<uint32_t, IO*> udp_ios_t;
	typedef tbb::concurrent_vector<IO*> ios_t;
	typedef tbb::concurrent_queue<IO*> avail_t;

	udp_ios_t udp_ios;
	ios_t ios;
	avail_t avail;

	ClientsThread **threads;
	size_t threads_count;
	size_t next_thread;

public:
	Clients();
	~Clients();

	void start();

	void connect_tcp(int socket, bool web, uint32_t ip);
	int connect_udp(uint32_t id, int socket, const sockaddr_in &addr);

	void disconnect(IO *io, int socket);
	void send(const server::Packet &packet);
};