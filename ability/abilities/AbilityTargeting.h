#pragma once

#include "battle/Combatant.h"			// combatant_ptr_t

#include <vector>
#include <functional>

class BattleField;

struct AbilityTargeting
{
	typedef std::vector<combatant_ptr_t> targets_t;
	typedef std::function<targets_t(combatant_ptr_t &caster, BattleField *field)> target_picker_t;

private:
	static targets_t all_enemy(combatant_ptr_t &caster, BattleField *field, bool with_summoner);
	static targets_t all_friend(combatant_ptr_t &caster, BattleField *field, bool with_summoner);
	static targets_t row_targets(combatant_ptr_t &caster, BattleField *field, bool enemy);

public:
	static targets_t front_target(combatant_ptr_t &caster, BattleField *field);
	static targets_t behind_target(combatant_ptr_t &caster, BattleField *field);
	static targets_t all_enemy_targets(combatant_ptr_t &caster, BattleField *field);
	static targets_t all_enemy_targets_with_summoner(combatant_ptr_t &caster, BattleField *field);
	static targets_t enemy_row_targets(combatant_ptr_t &caster, BattleField *field);
	static targets_t self_row_targets(combatant_ptr_t &caster, BattleField *field);
	static targets_t self(combatant_ptr_t &caster, BattleField *field);
	static targets_t self_fraction_targets(combatant_ptr_t &caster, BattleField *field);
	static targets_t all_friend_targets(combatant_ptr_t &caster, BattleField *field);
	static targets_t all_friend_targets_with_summoner(combatant_ptr_t &caster, BattleField *field);
};