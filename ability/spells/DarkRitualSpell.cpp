#include "DarkRitualSpell.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Summoner.h"

//#include "battle/Combatant.h"

DarkRitualSpell::DarkRitualSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana):
	Spell(type, ability::OTHER, level, cooldown, mana)
{}

bool DarkRitualSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	if (!target->is_card())
		return false;
/*
	std::set<uint16_t> choosed_ids;
	auto sacrificed_card = caster->get_summoner()->get_deck()->get_random_card(ActiveDeck::ON_FIELD, choosed_ids);

	if (sacrificed_card == nullptr)
		return false;

	auto sacrificed_combatant = std::make_shared<Combatant>(Combatant(sacrificed_card, caster->get_summoner()));
	uint16_t damage = sacrificed_card->get_health();
	field->damage(caster, sacrificed_combatant, damage);
	log.emplace_back(sacrificed_card->object_id(), DataPacker().pack(ability::ATTACK, damage));

	field->damage(caster, target, damage);
	log.emplace_back(target->object_id(), DataPacker().pack(ability::ATTACK, damage));
*/
	uint16_t damage = target->get_health();
	field->damage(caster, target, damage);
	log.emplace_back(target->object_id(), DataPacker().pack(ability::ATTACK, damage));

	auto opponent = field->get_opponent(caster->get_summoner());
	std::set<uint16_t> choosed_ids;
	auto damaged_card = opponent->get_deck()->get_random_card(ActiveDeck::ON_FIELD, choosed_ids);
	auto damaged_combatant = std::make_shared<Combatant>(Combatant(damaged_card, opponent));

	field->damage(caster, damaged_combatant, damage);
	log.emplace_back(damaged_card->object_id(), DataPacker().pack(ability::ATTACK, damage));

	return true;
}