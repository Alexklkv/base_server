#include "HealSpell.h"

#include "BattleField.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

HealSpell::HealSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, const Calculator *calculator, const picker_t &targeting):
	Spell(type, ability::OTHER_POSITIVE, level, cooldown, mana), calculator(calculator), picker(targeting)
{}

HealSpell::~HealSpell()
{
	delete this->calculator;
}

bool HealSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	int32_t value = this->calculator->get(target->get_max_health());
	value += caster->get_spell_strength_bonus(value);

	uint16_t changed = field->heal(caster, target, value);
	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::HEAL, changed));

	return true;
}

Spell::targets_t HealSpell::targets(combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	return this->picker(target, field);
}