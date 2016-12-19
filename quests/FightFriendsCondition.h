#pragma once

#include "Condition.h"

namespace quests
{

class FightFriendsCondition : public Condition
{
public:
	QuestType type() const override;

};

}