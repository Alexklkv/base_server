#include "QuestFinish.h"

namespace server
{

SERVER_PACKET_SOURCE(QuestFinish)

QuestFinish::QuestFinish(Status status, uint16_t quest_id)
{
	this->add(static_cast<uint8_t>(status));
	this->add(quest_id);

	this->write();
}

QuestFinish::QuestFinish(Status status, uint16_t quest_id, uint8_t reward_level, uint8_t reward_type, uint32_t reward_data)
{
	this->add(static_cast<uint8_t>(status));
	this->add(quest_id);
	this->add(reward_level);
	this->add(reward_type);
	this->add(reward_data);

	this->write();
}

}