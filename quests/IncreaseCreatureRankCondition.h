#pragma once

#include "Condition.h"

namespace quests
{

class IncreaseCreatureRankCondition : public Condition
{
public:
	QuestType type() const override;

};

}