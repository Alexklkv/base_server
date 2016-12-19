#include "ShieldSpell.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

ShieldSpell::ShieldSpell(uint32_t id, ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, const uint16_t value, const picker_t &targeting):
	Spell(type, ability::OTHER_POSITIVE, level, cooldown, mana), id(id), value(value), picker(targeting)
{}

bool ShieldSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField*) const
{
	if (!target->is_card())
		return false;

	auto card = target->get_card();

	card->add_shield(this->id, this->value);
	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::SHIELD_ACTION, (int16_t)this->value));

	return true;
}

Spell::targets_t ShieldSpell::targets(combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	return this->picker(target, field);
}