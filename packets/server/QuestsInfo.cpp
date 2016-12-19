#include "QuestsInfo.h"

#include "../../Quests.h"

namespace server
{

SERVER_PACKET_SOURCE(QuestsInfo)

QuestsInfo::QuestsInfo(const Quests *quests)
{
	this->add(quests);
	this->write();
}

}