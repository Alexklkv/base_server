#pragma once

#include "AbilityTargeting.h"			// AbilityTargeting::targets_t
#include "BattleAction.h"			// BattleAction::targets_t

#include "enums.h"

class BattleField;

class Ability
{
private:
	const ability::Type type;

protected:
	using targets_t = AbilityTargeting::targets_t;

	Ability(); /* Do not use this */
	explicit Ability(ability::Type type);

	virtual void do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const = 0;
	virtual targets_t targets(combatant_ptr_t &caster, BattleField *field) const = 0;

public:
	virtual ~Ability() = default;

	virtual void apply(BattleAction::targets_t &log, combatant_ptr_t &caster, BattleField *field) const;

	ability::Type get_ability() const;
};