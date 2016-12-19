#include "TargetingAbility.h"

TargetingAbility::TargetingAbility(const AbilityTargeting::target_picker_t &picker):
	picker(picker)
{}

Ability::targets_t TargetingAbility::targets(combatant_ptr_t &caster, BattleField *field) const
{
	return this->picker(caster, field);
}