#include "CardSharp.h"

namespace server
{

SERVER_PACKET_SOURCE(CardSharp)

CardSharp::CardSharp(bool is_sharped)
{
	this->add(static_cast<uint8_t>(is_sharped));

	this->write();
}

}