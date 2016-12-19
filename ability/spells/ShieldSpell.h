#pragma once

#include "Spell.h"
#include "SpellsTargeting.h"

#include "misc.h"

class ShieldSpell : public Spell
{
	using picker_t = SpellsTargeting::picker_t;
	using Calculator = calculators::ValueCalculator;

	uint32_t id;
	const uint16_t value;
	const picker_t picker;

protected:
	virtual bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	ShieldSpell(uint32_t id, ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, const uint16_t value, const picker_t &targeting);

	virtual targets_t targets(combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;
};