#include "SpoiledFolioEffect.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "Log.h"
#include "Summoner.h"

#include <algorithm>
#include <random>

SpoiledFolioEffect::SpoiledFolioEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::SPOLIED_FOLIO, 0, policy_factory)
{}

bool SpoiledFolioEffect::on_before_placement(CardAddContext &ctx) const
{
	thread_local std::mt19937 ENGINE;

	auto cards_set = ctx.actor->get_deck()->get_cards(ActiveDeck::UNUSED);
	std::vector<CardHandler*> cards(cards_set.cbegin(), cards_set.cend());
	std::shuffle(cards.begin(), cards.end(), ENGINE);

	for (CardHandler *card : cards)
	{
		combatant_ptr_t candidate = std::make_shared<Combatant>(card, ctx.actor);
		if (!ctx.field->can_add_card(candidate, ctx.slot, false))
			continue;

		ctx.card = candidate;

		return true;
	}

	return false;
}