#pragma once

#include "CardMask.h"

#include "battle/Combatant.h"

#include <functional>
#include <initializer_list>
#include <set>
#include <vector>

class BattleField;

class ComboTargeting
{
public:
	typedef std::set<combatant_ptr_t> targets_t;
	typedef std::function<targets_t(BattleField*, const combatant_ptr_t&)> picker_t;

private:
	static targets_t all(CardMask mask, Summoner *summoner);
	static targets_t row(CardMask mask, bool is_front, Summoner *summoner);
	static targets_t wedge(CardMask mask, bool is_reversed, uint8_t slot, Summoner *summoner);

public:
	static constexpr uint8_t WEDGE_SIZE = 3;

	static picker_t anywhere(CardMask mask, std::initializer_list<uint32_t> counts);
	static picker_t anywhere_from(CardMask mask, uint32_t count_from);
	static picker_t front_row(CardMask mask, uint32_t count_from);
	static picker_t back_row(CardMask mask, uint32_t count_from);
	static picker_t any_row(CardMask mask, uint32_t count_from);
	static picker_t straight_wedge(CardMask mask, uint32_t count_from);
	static picker_t reverse_wedge(CardMask mask, uint32_t count_from);
};