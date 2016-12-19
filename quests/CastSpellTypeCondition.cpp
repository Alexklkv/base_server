#include "CastSpellTypeCondition.h"

namespace quests
{

CastSpellTypeCondition::CastSpellTypeCondition(ability::Type spell):
	spell(spell)
{}

QuestType CastSpellTypeCondition::type() const
{
	return CAST_SPELL_TYPE;
}

bool CastSpellTypeCondition::compare(const Condition *condition) const
{
	if (!this->Condition::compare(condition))
		return false;

	return (this->spell == dynamic_cast<const CastSpellTypeCondition*>(condition)->spell);
}

}