#pragma once

#include "Condition.h"

namespace quests
{

class CastSpellsCondition : public Condition
{
public:
	QuestType type() const override;

};

}