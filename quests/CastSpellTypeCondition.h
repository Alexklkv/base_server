#pragma once

#include "Condition.h"

#include "../ability/Data.h"

namespace quests
{

class CastSpellTypeCondition : public Condition
{
	ability::Type spell;

public:
	CastSpellTypeCondition(ability::Type spell);

	QuestType type() const override;

	bool compare(const Condition *condition) const override;

};

}