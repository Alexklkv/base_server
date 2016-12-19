#pragma once

#include "Condition.h"

namespace quests
{

class CollectGoldCondition : public Condition
{
public:
	QuestType type() const override;

};

}