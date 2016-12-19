#include "RetrievalSpell.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Summoner.h"

RetrievalSpell::RetrievalSpell(ability::Type type, uint8_t level, uint8_t cooldown, uint8_t mana):
	Spell(type, ability::OTHER_NEGATIVE, level, cooldown, mana)
{}

bool RetrievalSpell::do_apply(BattleAction::targets_t &log, combatant_ptr_t&, combatant_ptr_t &target, BattleField *field) const
{
	if (target->is_card())
		throw Exception("Tried to use SPELL_RETRIEVAL on card");

	auto summoner = target->get_summoner();
	auto cards = summoner->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);
	for (auto &card : cards)
	{
		field->return_to_deck(std::make_shared<Combatant>(card, summoner));
		log.emplace_back(card->object_id(), DataPacker().pack(ability::Action::REMOVE));
	}

	return true;
}