#include "WrongSummonEffect.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "Log.h"
#include "Summoner.h"

WrongSummonEffect::WrongSummonEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::WRONG_SUMMON, 0, policy_factory)
{}

bool WrongSummonEffect::on_before_placement(CardAddContext &ctx) const
{
	thread_local std::mt19937 ENGINE;

	if (!ctx.card->is_card())
	{
		logger()->warning("Non-card combatant in wrong summon effect");
		return false;
	}

	auto grade = ctx.card->get_card()->get_grade();

	auto cards_set = ctx.card->get_summoner()->get_deck()->get_cards(ActiveDeck::UNUSED);
	std::vector<CardHandler*> cards(cards_set.begin(), cards_set.end());
	std::shuffle(cards.begin(), cards.end(), ENGINE);
	for (CardHandler *candidate_handler : cards)
	{
		combatant_ptr_t candidate = std::make_shared<Combatant>(candidate_handler, ctx.card->get_summoner());
		if (candidate_handler->get_grade() != grade || !ctx.field->can_add_card(candidate, ctx.slot, true))
			continue;

		ctx.card = candidate;
	}

	return true;
}