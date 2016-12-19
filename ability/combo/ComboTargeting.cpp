#include "ComboTargeting.h"

#include "ActiveDeck.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "CardMask.h"
#include "Exception.h"
#include "Summoner.h"

#include "battle/Combatant.h"

ComboTargeting::picker_t ComboTargeting::anywhere(CardMask mask, std::initializer_list<uint32_t> counts)
{
	std::set<uint32_t> copy(counts);
	return [mask, copy] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto result = all(mask, moved->get_summoner());
		if (copy.count(result.size()))
			return result;
		return targets_t();
	};
}

ComboTargeting::picker_t ComboTargeting::anywhere_from(CardMask mask, uint32_t count_from)
{
	return [mask, count_from] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto result = all(mask, moved->get_summoner());
		if (result.size() >= count_from)
			return result;
		return targets_t();
	};
}

ComboTargeting::picker_t ComboTargeting::front_row(CardMask mask, uint32_t count_from)
{
	return [mask, count_from] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto result = row(mask, true, moved->get_summoner());
		if (result.size() >= count_from)
			return result;
		return targets_t();
	};
}

ComboTargeting::picker_t ComboTargeting::back_row(CardMask mask, uint32_t count_from)
{
	return [mask, count_from] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto result = row(mask, false, moved->get_summoner());
		if (result.size() >= count_from)
			return result;
		return targets_t();
	};
}

ComboTargeting::picker_t ComboTargeting::straight_wedge(CardMask mask, uint32_t count_from)
{
	return [mask, count_from] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto result = wedge(mask, false, moved->get_card()->get_slot(), moved->get_summoner());
		if (result.size() >= WEDGE_SIZE)
			return result;
		return targets_t();
	};
}

ComboTargeting::picker_t ComboTargeting::reverse_wedge(CardMask mask, uint32_t count_from)
{
	return [mask, count_from] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto result = wedge(mask, true, moved->get_card()->get_slot(), moved->get_summoner());
		if (result.size() >= WEDGE_SIZE)
			return result;
		return targets_t();
	};
}

ComboTargeting::picker_t ComboTargeting::any_row(CardMask mask, uint32_t count_from)
{
	return [mask, count_from] (BattleField*, const combatant_ptr_t &moved) -> targets_t {
		if (!moved->is_card())
			return targets_t();

		if (!mask.compare_card(moved->get_card()))
			return targets_t();

		auto front = row(mask, true, moved->get_summoner());
		if (front.size() < count_from)
			front.clear();

		auto back = row(mask, false, moved->get_summoner());
		if (back.size() < count_from)
			back.clear();

		front.insert(back.begin(), back.end());
		return front;
	};
}

ComboTargeting::targets_t ComboTargeting::all(CardMask mask, Summoner *summoner)
{
	auto cards = summoner->get_deck()->get_cards(ActiveDeck::ON_FIELD);
	targets_t result;
	for (CardHandler *card : cards)
	{
		if (!mask.compare_card(card))
			continue;

		result.insert(std::make_shared<Combatant>(card, summoner));
	}
	return result;
}

ComboTargeting::targets_t ComboTargeting::row(CardMask mask, bool is_front, Summoner *summoner)
{
	uint8_t slot = (is_front) ? 0 : ActiveDeck::SLOTS_PER_LINE;
	auto cards = summoner->get_deck()->get_on_horizontal(slot);
	targets_t result;

	for (CardHandler *card : cards)
	{
		if (!mask.compare_card(card))
			continue;

		result.insert(std::make_shared<Combatant>(card, summoner));
	}

	return result;
}

ComboTargeting::targets_t ComboTargeting::wedge(CardMask mask, bool is_reversed, uint8_t slot, Summoner *summoner)
{
	auto cards = is_reversed ? summoner->get_deck()->get_on_reversed_wedge(slot) : summoner->get_deck()->get_on_wedge(slot);
	targets_t result;

	for (CardHandler *card : cards)
	{
		if (!mask.compare_card(card))
			continue;

		result.insert(std::make_shared<Combatant>(card, summoner));
	}

	return result;
}