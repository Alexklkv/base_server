#pragma once

#include "Spell.h"

#include "misc.h"

class ManaSourceSpell : public Spell
{
	using Calculator = calculators::ValueCalculator;

	const Calculator *calculator;
	const int8_t mana_change;

protected:
	virtual bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	ManaSourceSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, int8_t mana_change, const Calculator *calculator);
	~ManaSourceSpell();
};