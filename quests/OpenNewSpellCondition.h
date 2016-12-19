#pragma once

#include "Condition.h"

namespace quests
{

class OpenNewSpellCondition : public Condition
{
public:
	QuestType type() const override;

};

}