#include "CastSpellEffectCondition.h"

//#include "ability/spells/BattleSpellsParams.h"
//#include "ability/spells/Spell.h"

namespace quests
{

CastSpellEffectCondition::CastSpellEffectCondition(std::set<ability::Type> effects):
	effects(effects)
{}

CastSpellEffectCondition::CastSpellEffectCondition(ability::Type spell)
{
	this->effects.insert(spell);
}

CastSpellEffectCondition::~CastSpellEffectCondition()
{}

QuestType CastSpellEffectCondition::type() const
{
	return CAST_SPELL_EFFECT;
}

bool CastSpellEffectCondition::compare(const Condition *condition) const
{
	if (!this->Condition::compare(condition))
		return false;

	auto as_spell_effect_condition = dynamic_cast<const CastSpellEffectCondition*>(condition);
	for (auto effect : as_spell_effect_condition->effects)
	{
		if (this->effects.count(effect) == 0)
			return false;
	}

	return true;
}

}