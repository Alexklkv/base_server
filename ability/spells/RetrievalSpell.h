#pragma once

#include "Spell.h"

class RetrievalSpell final : public Spell
{
protected:
	bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	RetrievalSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana);
};