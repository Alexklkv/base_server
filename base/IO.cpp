#include "IO.h"

#include "BaseClient.h"
#include "BaseConfig.h"
#include "BaseServer.h"
#include "BufferRead.h"
#include "BufferWrite.h"
#include "Clients.h"
#include "Counters.h"
#include "HTTP.h"
#include "Log.h"

#include "util.h"

#include "client/Packet.h"
#include "server/Packet.h"

#include <boost/scoped_ptr.hpp>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#include <errno.h>
#include <ev++.h>
#include <openssl/sha.h>

#define WEBSOCKET_ANSWER	"HTTP/1.1 101 Web Socket Protocol Handshake\r\n" \
				"Access-Control-Allow-Origin: *\r\n" \
				"Connection: Upgrade\r\n" \
				"Upgrade: websocket\r\n" \
				"Sec-WebSocket-Accept: %s\r\n\r\n"

#define WEBSOCKET_GUID		"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

using boost::scoped_ptr;

IO::IO(const BaseConfig *config):
	status(Status::CLOSED), type(Type::BINARY), ip(0)
{
	this->socket_tcp = 0;
	this->socket_udp = 0;

	this->recv_buffer_udp = new char[config->UDP_BUFFER_SIZE];

	this->watcher_write_tcp = new ev::io();
	this->watcher_write_tcp->set<IO, &IO::on_write_tcp>(this);

	this->watcher_read_tcp = new ev::io();
	this->watcher_read_tcp->set<IO, &IO::on_read_tcp>(this);

	this->watcher_write_udp = new ev::io();
	this->watcher_write_udp->set<IO, &IO::on_write_udp>(this);

	this->watcher_read_udp = new ev::io();
	this->watcher_read_udp->set<IO, &IO::on_read_udp>(this);

	this->notifier_write_tcp = new ev::async();
	this->notifier_write_tcp->set<IO, &IO::on_notify_tcp>(this);

	this->notifier_write_udp = new ev::async();
	this->notifier_write_udp->set<IO, &IO::on_notify_udp>(this);

	this->notifier_start_udp = new ev::async();
	this->notifier_start_udp->set<IO, &IO::on_start_udp>(this);

	this->notifier_stop_udp = new ev::async();
	this->notifier_stop_udp->set<IO, &IO::on_stop_udp>(this);

	this->watcher_event = new ev::async();
	this->watcher_event->set<IO, &IO::on_event>(this);

	this->client = nullptr;

	logger()->debug("IO %p created", static_cast<void*>(this));
}

IO::~IO()
{
	delete this->client;

	delete this->watcher_event;

	delete this->notifier_stop_udp;
	delete this->notifier_start_udp;

	delete this->notifier_write_udp;
	delete this->notifier_write_tcp;

	delete this->watcher_read_udp;
	delete this->watcher_write_udp;
	delete this->watcher_read_tcp;
	delete this->watcher_write_tcp;

	delete [] this->recv_buffer_udp;

	logger()->debug("IO %p deleted", static_cast<void*>(this));
}

void IO::client_pair(BaseClient *client)
{
	this->client = client;
}

bool IO::tcp_stopped() const
{
	return (this->socket_tcp == 0);
}

bool IO::udp_stopped() const
{
	return (this->socket_udp == 0);
}

uint32_t IO::get_id() const
{
	return this->socket_tcp;
}

void IO::connect(Type type, uint32_t ip)
{
	this->type = type;
	this->ip = ip;
	this->status = Status::OPENED;
}

void IO::init_tcp(int socket, struct ev_loop *loop)
{
	this->socket_tcp = socket;

	this->watcher_write_tcp->set(loop);
	this->watcher_read_tcp->set(loop);
	this->watcher_write_udp->set(loop);
	this->watcher_read_udp->set(loop);

	this->notifier_write_tcp->set(loop);
	this->notifier_write_udp->set(loop);

	this->notifier_start_udp->set(loop);
	this->notifier_stop_udp->set(loop);

	this->watcher_event->set(loop);
}

void IO::start_tcp()
{
	this->send_buffer_tcp.clear();
	this->recv_buffer_tcp.clear();

	this->events.clear();

	this->watcher_write_tcp->start(this->socket_tcp, EV_WRITE);
	this->watcher_read_tcp->start(this->socket_tcp, EV_READ);

	this->notifier_write_tcp->start();
	this->watcher_event->start();

	this->notifier_start_udp->start();
	this->notifier_stop_udp->start();

	if (this->type == Type::BINARY)
		this->status = Status::WORKING;

	logger()->debug("IO %p started", static_cast<void*>(this));
}

int IO::start_udp(int socket)
{
	int current_socket = this->socket_udp.compare_and_swap(socket, 0);
	if (current_socket == 0)
	{
		this->notifier_start_udp->send();
		return socket;
	}

	logger()->debug("IO %p UDP already started", static_cast<void*>(this));
	return current_socket;
}

void IO::on_start_udp(ev::async &, int)
{
	this->notifier_start_udp->stop();

	this->send_buffer_udp.clear();

	this->watcher_write_udp->start(this->socket_udp, EV_WRITE);
	this->watcher_read_udp->start(this->socket_udp, EV_READ);

	this->notifier_write_udp->start();

	logger()->debug("IO %p started UDP", static_cast<void*>(this));
}

void IO::stop_udp()
{
	int close_socket = this->socket_udp.fetch_and_store(0);
	if (close_socket == 0)
	{
		logger()->debug("IO %p UDP already stopped", static_cast<void*>(this));

		this->notifier_start_udp->stop();
		this->notifier_stop_udp->stop();

		return;
	}

	if (::close(close_socket) < 0)
		logger()->warning("IO %p close UDP socket %d error %d", static_cast<void*>(this), close_socket, errno);

	this->notifier_stop_udp->send();
}

void IO::on_stop_udp(ev::async &, int)
{
	this->notifier_stop_udp->stop();

	this->notifier_write_udp->stop();

	this->watcher_read_udp->stop();
	this->watcher_write_udp->stop();

	this->send_buffer_udp.clear();

	logger()->debug("IO %p stopped UDP", static_cast<void*>(this));
}

void IO::stop_tcp()
{
	int close_socket = this->socket_tcp.fetch_and_store(0);
	if (close_socket == 0)
		return;

	this->stop_udp();

	shutdown(close_socket, SHUT_RDWR);
	if (::close(close_socket) < 0)
		logger()->warning("IO %p close socket %d error %d", static_cast<void*>(this), close_socket, errno);

	this->client->on_disconnect();

	this->watcher_event->stop();

	this->notifier_write_tcp->stop();

	this->watcher_read_tcp->stop();
	this->watcher_write_tcp->stop();

	this->send_buffer_tcp.clear();
	this->recv_buffer_tcp.clear();

	this->events.clear();

	logger()->debug("IO %p stopped", static_cast<void*>(this));

	clients()->disconnect(this, close_socket);
}

void IO::start_write_tcp()
{
	if (this->tcp_stopped())
		return;
	this->watcher_write_tcp->start();
}

void IO::start_write_udp()
{
	if (this->udp_stopped())
		return;
	this->watcher_write_udp->start();
}

void IO::stop_write_tcp()
{
	if (this->tcp_stopped())
		return;
	this->watcher_write_tcp->stop();
}

void IO::stop_write_udp()
{
	if (this->udp_stopped())
		return;
	this->watcher_write_udp->stop();
}

void IO::close()
{
	if (!this->tcp_stopped())
		shutdown(this->socket_tcp, SHUT_RD);
}

void IO::on_read_tcp(ev::io &, int)
{
	bool success = true;

	while (true)
	{
		int size = this->recv_buffer_tcp.read(this->socket_tcp);
		if (size > 0)
			continue;

		if (size < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			break;

		if (size < 0)
			logger()->debug("IO %p read TCP socket %d error %d", static_cast<void*>(this), this->socket_tcp.load(), errno);
		else
			logger()->debug("IO %p read TCP socket %d closed %d", static_cast<void*>(this), this->socket_tcp.load(), errno);

		success = false;
		break;
	}

	if (this->recv_buffer_tcp.policy())
	{
		logger()->debug("IO %p received policy request", static_cast<void*>(this));

		this->send_buffer_tcp.add(config()->CROSSDOMAIN, config()->CROSSDOMAIN_LENGTH);
		this->notifier_write_tcp->send();
		return;
	}

	while (success && this->type == Type::HTTP && this->status == Status::OPENED)
	{
		HTTP request;
		if (!this->recv_buffer_tcp.http(&request))
			break;

		/*request.origin != ""*/
		if (!request.valid || !request.has(HTTP::Field::CONNECTION, "Upgrade") || !request.has(HTTP::Field::UPGRADE, "Websocket") || !request.has(HTTP::Field::SEC_WEBSOCKET_KEY, nullptr))
		{
			logger()->warning("Received bad HTTP packet (%d) %s", request.valid, request.data);

			string buf;
			for (auto iter = request.header.begin(); iter != request.header.end(); ++iter)
				buf += std::to_string(static_cast<uint8_t>(iter->first)) + " => " + iter->second + "\n";
			logger()->warning("%s", buf.c_str());

			success = false;
			break;
		}

		string key = request.get(HTTP::Field::SEC_WEBSOCKET_KEY);
		key += WEBSOCKET_GUID;

		char *hash = sha1_get(key.c_str(), key.length(), false);
		char *accept = base64_get(hash, SHA_DIGEST_LENGTH);
		char *answer = format(WEBSOCKET_ANSWER, accept);

		this->status = Status::HANDSHAKE;
		this->type = Type::WEBSOCKET;

		this->send_buffer_tcp.add(answer, strlen(answer));
		this->notifier_write_tcp->send();

		free(hash);
		free(accept);
		free(answer);
		return;
	}

	while (true)
	{
		if (this->status != Status::WORKING)
			break;

		client::Packet *packet;
		if (this->type == Type::WEBSOCKET)
			packet = this->recv_buffer_tcp.web(success);
		else
			packet = this->recv_buffer_tcp.get();

		if (packet == nullptr)
			break;

		scoped_ptr<client::Packet> packet_ptr(packet);

		if (!packet_ptr->is_valid())
		{
			logger()->debug("IO %p received bad formed TCP packet", static_cast<void*>(this));
			success = false;
			break;
		}

		this->client->recv(packet);
	}

	if (!success)
		this->stop_tcp();
}

void IO::on_read_udp(ev::io &, int)
{
	while (true)
	{
		int size = recv(this->socket_udp, this->recv_buffer_udp, config()->UDP_BUFFER_SIZE, 0);
		if (size < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			return;

		if (size < 0)
		{
			logger()->debug("IO %p read UDP socket %d error %d", static_cast<void*>(this), this->socket_udp.load(), errno);
			return;
		}

		if (size < 6)
			continue;

		int32_t length = *reinterpret_cast<int32_t*>(this->recv_buffer_udp);
		size -= sizeof(length);

		if (length != size)
		{
			logger()->warning("IO %p received UDP packet with incorrect length: %d != %d", static_cast<void*>(this), length, size);
			return;
		}

		client::Packet packet(this->recv_buffer_udp + sizeof(length), length, BaseConfig::PROTOCOL_UDP, 0);

		if (!packet.is_valid())
		{
			logger()->debug("IO %p received bad formed UDP packet", static_cast<void*>(this));
			return;
		}

		this->client->recv(&packet);
	}
}

void IO::on_write_tcp(ev::io &, int)
{
	bool empty = false;
	bool success = true;

	while (true)
	{
		int size = this->send_buffer_tcp.write(this->socket_tcp, empty);
		if (size > 0)
			continue;

		if (size < 0 && (empty || errno == EAGAIN || errno == EWOULDBLOCK))
			break;

		if (size < 0)
			logger()->debug("IO %p write TCP socket %d error %d", static_cast<void*>(this), this->socket_tcp.load(), errno);
		else
			logger()->debug("IO %p write TCP socket %d closed %d", static_cast<void*>(this), this->socket_tcp.load(), errno);

		success = false;
		break;
	}

	if (empty)
		this->stop_write_tcp();

	if (empty && success && this->status == Status::HANDSHAKE)
		this->status = Status::WORKING;

	if (!success)
		this->stop_tcp();
}

void IO::on_write_udp(ev::io &, int)
{
	bool empty = false;

	while (true)
	{
		int size = this->send_buffer_udp.write(this->socket_udp, empty);
		if (size > 0)
			continue;

		if (size < 0 && (empty || errno == EAGAIN || errno == EWOULDBLOCK))
			break;

		if (size < 0)
			logger()->debug("IO %p write UDP socket %d error %d", static_cast<void*>(this), this->socket_udp.load(), errno);
		else
			logger()->debug("IO %p write UDP socket %d closed %d", static_cast<void*>(this), this->socket_udp.load(), errno);

		break;
	}

	if (empty)
		this->stop_write_udp();
}

void IO::on_event(ev::async &, int)
{
	ClientEvent event;
	while (this->events.try_pop(event))
		this->client->event(event);
}

void IO::on_notify_tcp(ev::async &, int)
{
	this->start_write_tcp();
}

void IO::on_notify_udp(ev::async &, int)
{
	this->start_write_udp();
}

void IO::send_tcp(const server::Packet &packet)
{
	if (this->tcp_stopped())
		return;

#ifdef DEBUG
	std::ostringstream dump;

	auto bucket = packet.get_bucket();
	const char * buffer = bucket->get_data();

	for (size_t i = 0; i < bucket->get_size(); ++i)
		dump << static_cast<unsigned>(static_cast<uint8_t>(buffer[i])) << " ";

	logger()->debug("Sending packet with length %" PRIu32 " data: %s", bucket->get_size(), dump.str().c_str());
#endif

	if (packet.need_logged() && !this->client->is_logged())
		return;

	this->send_buffer_tcp.add(packet, this->type == Type::WEBSOCKET);
	this->notifier_write_tcp->send();
}

void IO::send_udp(const server::Packet &packet)
{
	if (this->udp_stopped())
		return;

	if (packet.need_logged() && !this->client->is_logged())
		return;

	this->send_buffer_udp.add(packet, this->type == Type::WEBSOCKET);
	this->notifier_write_udp->send();
}

void IO::event(uint8_t type, uint32_t sender_id, uint32_t data)
{
	if (this->tcp_stopped())
		return;

	ClientEvent event;
	event.type = type;
	event.sender_id = sender_id;
	event.data = data;

	this->events.push(event);
	this->watcher_event->send();
}