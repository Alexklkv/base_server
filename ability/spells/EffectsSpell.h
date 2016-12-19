#pragma once

#include "Spell.h"
#include "SpellsTargeting.h"

#include <vector>

class BattleEffect;

class EffectsSpell : public Spell
{
	using picker_t = SpellsTargeting::picker_t;

	const picker_t picker;
	std::vector<const BattleEffect*> effects;

protected:
	virtual bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	EffectsSpell(ability::Type type, ability::Effect effect_type, uint8_t level, uint8_t cooldown, uint8_t mana, const picker_t &targeting, std::initializer_list<const BattleEffect*> effects);
	virtual ~EffectsSpell();

	virtual targets_t targets(combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;
};