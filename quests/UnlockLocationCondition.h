#pragma once

#include "Condition.h"

namespace quests
{

class UnlockLocationCondition : public Condition
{
public:
	QuestType type() const override;

};

}