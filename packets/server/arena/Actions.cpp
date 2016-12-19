#include "Actions.h"

#include "battle/RoundActionsLog.h"
#include "server/Group.h"

namespace server
{

namespace arena
{

SERVER_PACKET_SOURCE(Actions)

Actions::Actions(const RoundActionsLog *actions)
{
	this->add(actions);
	this->write();
}

}

}