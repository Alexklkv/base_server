#include "Chat.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(Chat)

Chat::Chat(const char *message)
{
	this->add(message);
	this->write();
}

}

}