#pragma once

#include "Spell.h"
#include "SpellsTargeting.h"

#include "misc.h"

class DamageSpell : public Spell
{
	using picker_t = SpellsTargeting::picker_t;
	using Calculator = calculators::ValueCalculator;

	const Calculator *calculator;
	const picker_t picker;

protected:
	virtual bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	DamageSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, const Calculator *calculator, const picker_t &targeting);
	~DamageSpell();

	virtual targets_t targets(combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;
};