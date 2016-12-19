#pragma once

#include "battle/Combatant.h"

#include <functional>
#include <list>

class BattleField;

class SpellsTargeting
{
public:
	typedef std::list<combatant_ptr_t> targets_t;
	typedef std::function<targets_t(const combatant_ptr_t &target, const BattleField *field)> picker_t;
	typedef std::function<bool(const combatant_ptr_t&)> predicate_t;

	static picker_t self();
	static picker_t n_neighbours(uint8_t count);
	static picker_t all_cards();

	static picker_t combine(std::initializer_list<picker_t> pickers);

	static predicate_t any();
	static predicate_t damaged();
};