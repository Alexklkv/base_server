#include "AwakeningSpell.h"

#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"

#include "battle/RoundActionsLog.h"

AwakeningSpell::AwakeningSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana):
	Spell(type, ability::OTHER_POSITIVE, level, cooldown, mana)
{}

bool AwakeningSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField*) const
{
	if (!target->is_card())
		throw Exception("Awakening spell casted on non-card entity");

	target->get_card()->used = false;
	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::UNBLOCK));

	return true;
}