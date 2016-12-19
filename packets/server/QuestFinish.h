#pragma once

#include "../../enums.h"
#include "server/Packet.h"

namespace server
{

class QuestFinish : public Packet
{
	SERVER_PACKET_HEADER(QuestFinish)

public:
	enum Status : uint8_t
	{
		SUCCESS = 0,
		FAILED
	};

	QuestFinish(Status status, uint16_t quest_id);
	QuestFinish(Status status, uint16_t quest_id, uint8_t reward_level, uint8_t reward_type, uint32_t reward_data);

};

}