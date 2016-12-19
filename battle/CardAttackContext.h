#pragma once

#include "BattleAction.h"
#include "CardActionContext.h"
#include "Combatant.h"

class BattleField;

class CardAttackContext : public CardActionContext
{
	bool updated = false;
	bool forbidden = false;
	bool blocked = false;

	BattleAction::AttackType attack_type = BattleAction::AttackType::ATTACK_FAILED;

public:
	combatant_ptr_t attacker;
	combatant_ptr_t target;
	float damage_modifier;
	int32_t extra_damage = 0;
	float dodge_chance = 0;
	float critical_chance = 0;

	bool by_player;
	bool is_response;

	CardAttackContext(BattleField *field, combatant_ptr_t &attacker, combatant_ptr_t &target, bool by_player, bool is_response, float damage_modifier, BattleAction::targets_t &targets);

	void update_damage();

	int32_t get_total_damage() const;
	BattleAction::AttackType result() const;
	bool is_possible() const;
	bool is_blocked() const;
	bool is_success() const;

	void forbid();	// Means this action is impossible. Is not written to actions log.
	void block();	// Means this attack was blocked by target effect.
};