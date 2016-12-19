#pragma once

#include "BattleAction.h"
#include "SpellsTargeting.h"

#include "battle/CardSpellContext.h"
#include "battle/Combatant.h"

#include "enums.h"

class BattleField;

class Spell
{
protected:
	virtual bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const = 0;

public:
	typedef SpellsTargeting::targets_t targets_t;

	const ability::Type spell;
	ability::Effect effect_type;
	const uint8_t level;
	const uint8_t cooldown;
	const uint8_t mana;

	Spell(ability::Type spell, ability::Effect effect_type, uint8_t level, uint8_t cooldown, uint8_t mana);
	virtual ~Spell();

	bool can_cast(combatant_ptr_t &caster, combatant_ptr_t target) const;
	bool is_positive() const;
	bool is_negative() const;

	bool apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const;
	virtual targets_t targets(combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const;
};