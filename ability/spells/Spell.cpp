#include "Spell.h"

Spell::Spell(ability::Type spell, ability::Effect effect_type, uint8_t level, uint8_t cooldown, uint8_t mana):
	spell(spell), effect_type(effect_type), level(level), cooldown(cooldown), mana(mana)
{}

Spell::~Spell()
{}

bool Spell::apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	return this->do_apply(log, caster, target, field);
}

Spell::targets_t Spell::targets(combatant_ptr_t&, combatant_ptr_t &target, BattleField*) const
{
	// The default target is 'target'.
	return {target};
}

bool Spell::is_positive() const
{
	return (this->effect_type == ability::OTHER_POSITIVE || this->effect_type == ability::OTHER);
}

bool Spell::is_negative() const
{
	return (this->effect_type == ability::OTHER_NEGATIVE || this->effect_type == ability::OTHER);
}

bool Spell::can_cast(combatant_ptr_t &caster, combatant_ptr_t target) const
{
	bool can_use = false;
	can_use = can_use || (this->is_positive() && (caster->object_id().summoner_id == target->object_id().summoner_id));
	can_use = can_use || (this->is_negative() && (caster->object_id().summoner_id != target->object_id().summoner_id));

	return can_use;
}