#include "AsyncAward.h"

namespace server
{

SERVER_PACKET_SOURCE(AsyncAward)

AsyncAward::AsyncAward(uint16_t card_type, uint8_t card_level)
{

	this->add(card_type);
	this->add(card_level);
	this->write();
}

}