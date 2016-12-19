#pragma once

#include "EventListener.h"
#include "NoCopy.h"

class IO;
struct ClientEvent;

namespace client
{
	class Packet;
}

namespace server
{
	class Packet;
}

class BaseClient : public EventListener, private NoCopy
{
	friend class IO;

private:
	IO *io;

	virtual bool is_logged() const = 0;

	virtual void recv(const client::Packet *packet) = 0;
	virtual void event(const ClientEvent &event) = 0;

	virtual void on_disconnect() = 0;

protected:
	void disconnect();

public:
	explicit BaseClient(IO *io);

	uint32_t get_tcp() const;

	void send(const server::Packet &packet);
	void send_udp(const server::Packet &packet);

	void event(uint8_t type, uint32_t sender_id = 0, uint32_t data = 0);
};