#include "TurnFinished.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(TurnFinished)

TurnFinished::TurnFinished()
{
	this->write();
}

}

}