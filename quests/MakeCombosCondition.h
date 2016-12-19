#pragma once

#include "Condition.h"

namespace quests
{

class MakeCombosCondition : public Condition
{
public:
	QuestType type() const override;
};

}