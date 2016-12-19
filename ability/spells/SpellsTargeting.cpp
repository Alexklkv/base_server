#include "SpellsTargeting.h"

#include "ActiveDeck.h"
#include "CardHandler.h"
#include "Exception.h"
#include "Summoner.h"

#include "battle/Combatant.h"

SpellsTargeting::picker_t SpellsTargeting::self()
{
	return [] (const combatant_ptr_t &target, const BattleField*) -> targets_t {
		return {target};
	};
}

static SpellsTargeting::targets_t cards_wrap(const cards_set_t &cards, Summoner *summoner)
{
	SpellsTargeting::targets_t result;
	for (CardHandler *card : cards)
		result.push_back(std::make_shared<Combatant>(card, summoner));
	return result;
}

SpellsTargeting::picker_t SpellsTargeting::n_neighbours(uint8_t count)
{
	return [count] (const combatant_ptr_t &target, const BattleField*) {
		if (!target->is_card())
			throw Exception("Non-card supplied to neighbours targets picker");

		auto candidates = target->get_summoner()->get_deck()->get_neighbours_around(target->get_card());
		if (candidates.size() > count)
			candidates.erase(std::next(candidates.cbegin(), count), candidates.cend());

		return cards_wrap(candidates, target->get_summoner());
	};
}

SpellsTargeting::picker_t SpellsTargeting::all_cards()
{
	return [] (const combatant_ptr_t &target, const BattleField*) {
		auto candidates = target->get_summoner()->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);
		return cards_wrap(candidates, target->get_summoner());
	};
}

SpellsTargeting::picker_t SpellsTargeting::combine(std::initializer_list<picker_t> pickers)
{
	std::vector<picker_t> copy(pickers);
	return [copy] (const combatant_ptr_t &target, const BattleField *field) {
		targets_t targets;
		for (const picker_t &picker : copy)
		{
			auto current = picker(target, field);
			targets.splice(targets.end(), std::move(current));
		}
		return targets;
	};
}

SpellsTargeting::predicate_t SpellsTargeting::any()
{
	return [] (const combatant_ptr_t&) { return true; };
}

SpellsTargeting::predicate_t SpellsTargeting::damaged()
{
	return [] (const combatant_ptr_t &target) {
		return target->get_health() < target->get_max_health();
	};
}