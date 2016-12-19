#include "AbilityTargeting.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "Summoner.h"

AbilityTargeting::targets_t AbilityTargeting::all_enemy(combatant_ptr_t &caster, BattleField *field, bool with_summoner)
{
	targets_t targets;
	Summoner *opponent = field->get_opponent(caster->get_summoner());

	if (with_summoner)
		targets.push_back(std::make_shared<Combatant>(opponent));

	auto cards = opponent->get_deck()->get_cards(ActiveDeck::ON_FIELD);
	for (auto card : cards)
		targets.push_back(std::make_shared<Combatant>(card, opponent));

	return targets;
}

AbilityTargeting::targets_t AbilityTargeting::all_friend(combatant_ptr_t &caster, BattleField*, bool with_summoner)
{
	targets_t targets;
	Summoner *owner = caster->get_summoner();

	if (with_summoner)
		targets.push_back(caster);

	auto cards = owner->get_deck()->get_cards(ActiveDeck::ON_FIELD);
	for (auto card : cards)
		targets.push_back(std::make_shared<Combatant>(card, owner));

	return targets;
}

AbilityTargeting::targets_t AbilityTargeting::row_targets(combatant_ptr_t &caster, BattleField *field, bool enemy)
{
	if (!caster->is_card())
		return {};

	Summoner *target_summoner = caster->get_summoner();
	if (enemy)
		target_summoner = field->get_opponent(target_summoner);

	targets_t targets;
	CardHandler *caster_card = caster->get_card();

	auto row = target_summoner->get_deck()->get_on_vertical(caster_card->get_slot());
	for (auto card : row)
	{
		if (card != caster_card)
			targets.push_back(std::make_shared<Combatant>(card, target_summoner));
	}

	return targets;
}

AbilityTargeting::targets_t AbilityTargeting::behind_target(combatant_ptr_t &caster, BattleField*)
{
	if (!caster->is_card())
		return {};

	targets_t targets;

	Summoner *summoner = caster->get_summoner();

	auto cards = summoner->get_deck()->get_cards_behind(caster->get_card()->get_slot());
	for (auto card : cards)
		targets.push_back(std::make_shared<Combatant>(card, summoner));
	return targets;
}

AbilityTargeting::targets_t AbilityTargeting::front_target(combatant_ptr_t &caster, BattleField*)
{
	if (!caster->is_card())
		return {};

	Summoner *summoner = caster->get_summoner();

	CardHandler *front = summoner->get_deck()->get_front_card(caster->get_card()->get_slot());
	if (front == nullptr)
		return {};

	return {std::make_shared<Combatant>(front, summoner)};
}

AbilityTargeting::targets_t AbilityTargeting::all_enemy_targets(combatant_ptr_t &caster, BattleField *field)
{
	return all_enemy(caster, field, false);
}

AbilityTargeting::targets_t AbilityTargeting::all_enemy_targets_with_summoner(combatant_ptr_t &caster, BattleField *field)
{
	return all_enemy(caster, field, true);
}

AbilityTargeting::targets_t AbilityTargeting::enemy_row_targets(combatant_ptr_t &caster, BattleField *field)
{
	return row_targets(caster, field, true);
}

AbilityTargeting::targets_t AbilityTargeting::self_row_targets(combatant_ptr_t &caster, BattleField *field)
{
	return row_targets(caster, field, false);
}

AbilityTargeting::targets_t AbilityTargeting::self(combatant_ptr_t &caster, BattleField*)
{
	return {caster};
}

AbilityTargeting::targets_t AbilityTargeting:: self_fraction_targets(combatant_ptr_t &caster, BattleField*)
{
	if (!caster->is_card())
		return {};

	targets_t targets;

	Summoner *target_summoner = caster->get_summoner();
	CardHandler *caster_card = caster->get_card();

	auto active_cards = target_summoner->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);
	for (auto card : active_cards)
	{
		if (card != caster_card && card->get_fraction() == caster_card->get_fraction())
			targets.push_back(std::make_shared<Combatant>(card, target_summoner));
	}

	return targets;
}

AbilityTargeting::targets_t AbilityTargeting::all_friend_targets(combatant_ptr_t &caster, BattleField *field)
{
	return all_friend(caster, field, false);
}

AbilityTargeting::targets_t AbilityTargeting::all_friend_targets_with_summoner(combatant_ptr_t &caster, BattleField *field)
{
	return all_friend(caster, field, true);
}