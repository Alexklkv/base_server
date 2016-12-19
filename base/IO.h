#pragma once

#include "BufferRead.h"
#include "BufferWrite.h"
#include "ClientEvent.h"
#include "EventListener.h"
#include "NoCopy.h"

#include "server/Packet.h"

#include <atomic.h>
#include <concurrent_queue.h>

namespace ev
{
	struct async;
	struct io;
}

class BaseClient;
class BaseConfig;

using tbb::atomic;

class IO : public EventListener, private NoCopy
{
public:
	enum class Type : uint8_t
	{
		BINARY = 0,
		HTTP,
		WEBSOCKET
	};

private:
	enum class Status : uint8_t
	{
		OPENED = 0,
		HANDSHAKE,
		WORKING,
		CLOSED
	};

	atomic<int> socket_tcp;
	atomic<int> socket_udp;

	BaseClient *client;
	Status status;
	Type type;

	ev::io *watcher_read_tcp;
	ev::io *watcher_write_tcp;
	ev::io *watcher_read_udp;
	ev::io *watcher_write_udp;

	ev::async *notifier_write_tcp;
	ev::async *notifier_write_udp;

	ev::async *notifier_start_udp;
	ev::async *notifier_stop_udp;

	ev::async *watcher_event;

	BufferRead recv_buffer_tcp;
	BufferWrite send_buffer_tcp;

	BufferWrite send_buffer_udp;
	char *recv_buffer_udp;

	tbb::concurrent_queue<ClientEvent> events;

	void stop_udp();

	void stop_write_tcp();
	void start_write_tcp();
	void stop_write_udp();
	void start_write_udp();

	void on_read_tcp(ev::io &w, int revets);
	void on_write_tcp(ev::io &w, int revents);
	void on_read_udp(ev::io &w, int revets);
	void on_write_udp(ev::io &w, int revents);

	void on_notify_tcp(ev::async &w, int revents);
	void on_notify_udp(ev::async &w, int revents);

	void on_start_udp(ev::async &w, int revents);
	void on_stop_udp(ev::async &w, int revents);

	void on_event(ev::async &w, int revents);

public:
	uint32_t ip;

	IO(const BaseConfig *config);
	virtual ~IO();

	virtual void client_pair(BaseClient *client);

	bool tcp_stopped() const;
	bool udp_stopped() const;

	uint32_t get_id() const;

	void connect(Type type, uint32_t ip);

	void init_tcp(int socket, struct ev_loop *loop);

	void start_tcp();
	int start_udp(int socket);

	void stop_tcp();
	void close();

	virtual void send_tcp(const server::Packet &packet);
	virtual void send_udp(const server::Packet &packet);

	virtual void event(uint8_t type, uint32_t sender_id = 0, uint32_t data = 0);
};