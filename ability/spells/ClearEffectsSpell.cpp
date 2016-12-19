#include "ClearEffectsSpell.h"

#include "BattleField.h"
#include "DataPacker.h"

#include "ability/effects/types.h"
#include "battle/RoundActionsLog.h"

ClearEffectsSpell::ClearEffectsSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, EffectType target_effects):
	Spell(type, ability::OTHER_POSITIVE, level, cooldown, mana), target_effects(target_effects)
{}

void ClearEffectsSpell::clear(BattleAction::targets_t &log, BattleField *field, combatant_ptr_t&, combatant_ptr_t &target, bool negative) const
{
	auto removed = field->clear_effects(target, negative);
	for (const EffectID &entry : removed)
		log.emplace_back(target.get(), DataPacker().pack(ability::CLEAR_EFFECT, entry.type, entry.modifier));
}

bool ClearEffectsSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	if (this->target_effects == EffectType::NEGATIVE || this->target_effects == EffectType::ALL)
		clear(log, field, caster, target, true);
	if (this->target_effects == EffectType::POSITIVE || this->target_effects == EffectType::ALL)
		clear(log, field, caster, target, false);

	return true;
}