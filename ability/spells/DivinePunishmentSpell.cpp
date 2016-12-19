#include "DivinePunishmentSpell.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Summoner.h"

DivinePunishmentSpell::DivinePunishmentSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana, uint16_t to_card_type):
	Spell(type, ability::OTHER, level, cooldown, mana), target_type(to_card_type)
{}

bool DivinePunishmentSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	if (!target->is_card())
		throw Exception("Tried to use SPELL_DIVINE_PUNISHMENT not on card");

	auto summoner = target->get_summoner();
	auto card = target->get_card();
	auto deck = summoner->get_deck();

	CardHandler *new_card = card->create_prototype(card->get_id(), summoner, this->target_type);
	uint8_t slot = card->get_slot();

	field->return_to_deck(target);
	deck->replace(card, new_card);
	field->add_card(summoner->get_id(), new_card->get_id(), slot, false);

	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::TRANSFORM, new_card->get_type()));

	return true;
}