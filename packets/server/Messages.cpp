#include "Messages.h"

namespace server
{

SERVER_PACKET_SOURCE(Messages)

Messages::Messages(uint32_t interlocutor_id, const Group &messages)
{
	this->add(interlocutor_id);
	this->add(&messages);

	this->write();
}

}