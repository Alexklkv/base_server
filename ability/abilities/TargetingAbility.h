#pragma once

#include "Ability.h"			// Ability

class TargetingAbility : public virtual Ability
{
private:
	const AbilityTargeting::target_picker_t picker;

protected:
	explicit TargetingAbility(const AbilityTargeting::target_picker_t &picker);

	virtual Ability::targets_t targets(combatant_ptr_t &caster, BattleField *field) const override;
};