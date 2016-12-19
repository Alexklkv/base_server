#include "LibraryMessSpell.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Summoner.h"

LibraryMessSpell::LibraryMessSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana):
	Spell(type, ability::OTHER_NEGATIVE, level, cooldown, mana)
{}

bool LibraryMessSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	if (!target->is_card())
		throw Exception("Tried to use SPELL_LIBRARY_MESS not on card");

	auto summoner = target->get_summoner();
	auto card = target->get_card();
	auto deck = summoner->get_deck();

	auto new_card = deck->get_random_card_for_slot(ActiveDeck::CardState::UNUSED, card->get_slot());
	if (new_card == nullptr)
		return false;

	field->return_to_deck(target);
	field->add_card(summoner->get_id(), new_card->get_id(), card->get_slot(), false);

	log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::REMOVE));
	log.emplace_back(GameObject::Id{new_card->get_id(), summoner->get_id()}, DataPacker().pack(ability::Action::ADD_ON_SLOT, new_card->get_slot()));

	return true;
}