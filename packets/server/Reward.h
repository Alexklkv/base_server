#pragma once

#include "DelayedReward.h"

#include "server/Packet.h"

namespace server
{

class Reward : public Packet
{
	SERVER_PACKET_HEADER(Reward)

public:
	Reward(DelayedReward::Category category, uint32_t data, const GameItems &items);
};

}