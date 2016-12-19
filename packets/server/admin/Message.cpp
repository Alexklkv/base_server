#include "Message.h"

namespace server
{

namespace admin
{

SERVER_PACKET_SOURCE(Message)

Message::Message(const char *message)
{
	this->add(message);

	this->write();
}

}

}