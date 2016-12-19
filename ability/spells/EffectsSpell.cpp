#include "EffectsSpell.h"

#include "BattleField.h"
#include "DataPacker.h"

#include "ability/effects/basic/BattleEffect.h"
#include "battle/RoundActionsLog.h"

EffectsSpell::EffectsSpell(ability::Type type, ability::Effect effect_type, uint8_t level, uint8_t cooldown, uint8_t mana, const picker_t &targeting, std::initializer_list<const BattleEffect*> effects):
	Spell(type, effect_type, level, cooldown, mana), picker(targeting), effects(effects)
{}

EffectsSpell::~EffectsSpell()
{
	for (auto effect : this->effects)
		delete effect;
}

bool EffectsSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	for (const BattleEffect *effect : this->effects)
		field->add_effect(caster, target, effect, log);

	return true;
}

Spell::targets_t EffectsSpell::targets(combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	return this->picker(target, field);
}