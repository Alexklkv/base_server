#pragma once

#include "../../enums.h"
#include "server/Packet.h"

namespace server
{

class QuestProgress : public Packet
{
	SERVER_PACKET_HEADER(QuestProgress)

public:
	QuestProgress(uint16_t quest_id, uint32_t current_progress);

};

}