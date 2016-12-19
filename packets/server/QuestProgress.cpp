#include "QuestProgress.h"

namespace server
{

SERVER_PACKET_SOURCE(QuestProgress)

QuestProgress::QuestProgress(uint16_t quest_id, uint32_t current_progress)
{
	this->add(quest_id);
	this->add(current_progress);

	this->write();
}

}