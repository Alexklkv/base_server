#include "DamageSpell.h"

#include "BattleField.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

DamageSpell::DamageSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, const Calculator *calculator, const picker_t &targeting):
	Spell(type, ability::OTHER_NEGATIVE, level, cooldown, mana), calculator(calculator), picker(targeting)
{}

DamageSpell::~DamageSpell()
{
	delete this->calculator;
}

bool DamageSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	int16_t value = this->calculator->get(target->get_damage());
	value += caster->get_spell_strength_bonus(value);
	value -= std::round((value * target->get_magic_resistance()) / 100.f);

	field->damage(caster, target, value);
	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::ATTACK, (int16_t)value));
	return true;
}

Spell::targets_t DamageSpell::targets(combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	return this->picker(target, field);
}