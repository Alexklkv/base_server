#pragma once

#include "Condition.h"

namespace quests
{

class WeeklyQuestsCondition : public Condition
{
public:
	virtual QuestType type() const override;

};

}