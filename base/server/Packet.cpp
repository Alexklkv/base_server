#include "Packet.h"

namespace server
{

static const uint16_t PACKET_INIT_SIZE = 256;

Packet::Packet():
	Packet(PACKET_INIT_SIZE)
{}

Packet::Packet(uint32_t start_size):
	Writer(start_size)
{
	this->add(static_cast<uint32_t>(0));	// size
	this->add(static_cast<uint16_t>(0));	// type
}

void Packet::write()
{
	* (uint32_t *) (this->get_data()) = this->get_size() - sizeof(uint32_t);
	* (uint16_t *) (this->get_data() + sizeof(uint32_t)) = this->get_type();
}

}