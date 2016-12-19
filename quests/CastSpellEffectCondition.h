#pragma once

#include "Condition.h"

#include "../QuestsParams.h"
#include "../ability/Data.h"

#include <set>

namespace quests
{

class CastSpellEffectCondition : public Condition
{
	friend class ::QuestsParams;

private:
	std::set<ability::Type> effects;

	CastSpellEffectCondition(std::set<ability::Type> effects);

public:
	CastSpellEffectCondition(ability::Type spell);
	~CastSpellEffectCondition();

	QuestType type() const override;

	bool compare(const Condition *condition) const override;
};

}