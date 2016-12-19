#include "NextRound.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(NextRound)

NextRound::NextRound()
{
	this->write();
}

}

}