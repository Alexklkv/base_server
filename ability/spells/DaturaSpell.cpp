#include "DaturaSpell.h"

#include "DataPacker.h"
#include "Log.h"

DaturaSpell::DaturaSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana):
	Spell(type, ability::OTHER_NEGATIVE, level, cooldown, mana)
{}

bool DaturaSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField*) const
{
	if (!target->is_summoner())
		throw Exception("Applying datura spell on non-summoner combatant");

	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::UNBLOCK));
	return true;
}