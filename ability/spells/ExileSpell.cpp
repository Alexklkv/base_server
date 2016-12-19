#include "ExileSpell.h"

#include "BattleField.h"
#include "DataPacker.h"

ExileSpell::ExileSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, const picker_t &targets):
	Spell(type, ability::OTHER_NEGATIVE, level, cooldown, mana), picker(targets)
{}

bool ExileSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	if (target->is_dead())
		return false;

	field->return_to_deck(target);
	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::REMOVE));

	return true;
}

Spell::targets_t ExileSpell::targets(combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	return this->picker(target, field);
}