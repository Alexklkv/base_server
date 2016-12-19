#include "BaseClient.h"

#include "IO.h"

BaseClient::BaseClient(IO *io):
	io(io)
{}

void BaseClient::disconnect()
{
	this->io->stop_tcp();
}

uint32_t BaseClient::get_tcp() const
{
	return this->io->get_id();
}

void BaseClient::send(const server::Packet &packet)
{
	this->io->send_tcp(packet);
}

void BaseClient::send_udp(const server::Packet &packet)
{
	this->io->send_udp(packet);
}

void BaseClient::event(uint8_t type, uint32_t sender_id, uint32_t data)
{
	this->io->event(type, sender_id, data);
}