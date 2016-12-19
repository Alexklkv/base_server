#include "AstralPortalSpell.h"

#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Summoner.h"

AstralPortalSpell::AstralPortalSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana):
	Spell(type, ability::OTHER_POSITIVE, level, cooldown, mana)
{}

bool AstralPortalSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField*) const
{
	if (!target->is_summoner())
		throw Exception("Tried to use SPELL_ASTRAL_PORTAL not on summoner");

	const CardHandler *new_card = target->get_summoner()->summon_new_card();
	if (new_card == nullptr)
		return false;

	log.emplace_back(target->object_id(), DataPacker().pack(ability::SUMMON, new_card->get_id()));

	return true;
}