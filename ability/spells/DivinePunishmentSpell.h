#pragma once

#include "Spell.h"

class DivinePunishmentSpell final : public Spell
{
private:
	const uint16_t target_type;

	bool do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	DivinePunishmentSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, uint16_t to_card_type);
};