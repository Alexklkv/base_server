#pragma once

#include "Spell.h"

class ClearEffectsSpell : public Spell
{
public:
	enum class EffectType
	{
		POSITIVE,
		NEGATIVE,
		ALL
	};

private:
	const EffectType target_effects;

	void clear(BattleAction::targets_t &log, BattleField *field, combatant_ptr_t &caster, combatant_ptr_t &target, bool negative) const;
	bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	ClearEffectsSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, EffectType target_effects);
};