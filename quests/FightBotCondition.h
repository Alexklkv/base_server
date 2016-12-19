#pragma once

#include "Condition.h"

namespace quests
{

class FightBotCondition : public Condition
{
public:
	QuestType type() const override;
};

}