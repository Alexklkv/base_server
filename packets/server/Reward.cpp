#include "Reward.h"

#include "Enum.h"

namespace server
{

SERVER_PACKET_SOURCE(Reward)

Reward::Reward(DelayedReward::Category category, uint32_t data, const GameItems &items)
{
	this->add(enum_unwrap(category));
	this->add(data);
	this->add(items);

	this->write();
}

}