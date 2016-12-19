#pragma once

#include "server/Packet.h"

class Quests;

namespace server
{

class QuestsInfo : public Packet
{
	SERVER_PACKET_HEADER(QuestsInfo)

public:
	QuestsInfo(const Quests *quests);

};

}