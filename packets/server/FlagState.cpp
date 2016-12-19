#include "FlagState.h"

#include "Flags.h"

namespace server
{

SERVER_PACKET_SOURCE(FlagState)

FlagState::FlagState(FlagType type, uint16_t flag)
{
	this->add(static_cast<uint8_t>(type));
	this->add(static_cast<uint16_t>(flag));

	this->write();
}

}