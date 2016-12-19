#pragma once

#include "Condition.h"

namespace quests
{

class GainNewLevelCondition : public Condition
{
public:
	QuestType type() const override;
};

}