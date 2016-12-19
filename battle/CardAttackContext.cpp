#include "CardAttackContext.h"

#include "BattleAction.h"
#include "Enum.h"
#include "Exception.h"
#include "Log.h"
#include "Random.h"

CardAttackContext::CardAttackContext(BattleField *field, combatant_ptr_t &attacker, combatant_ptr_t &target, bool by_player, bool is_response, float damage_modifier, BattleAction::targets_t &targets):
	CardActionContext(field, targets),
	attacker(attacker),
	target(target),
	damage_modifier(damage_modifier),
	by_player(by_player),
	is_response(is_response)
{}

void CardAttackContext::update_damage()
{
	this->updated = true;
	this->attack_type = BattleAction::AttackType::ATTACK_NORMAL;

	if (this->is_blocked())
		this->extra_damage = -this->attacker->get_damage();
	else if (Random::chance(this->dodge_chance))
		this->attack_type = BattleAction::AttackType::ATTACK_DODGE;
	else if (Random::chance(this->critical_chance))
	{
		this->attack_type = BattleAction::AttackType::ATTACK_CRITICAL;
		this->extra_damage += this->get_total_damage() * this->attacker->get_critical_strength_bonus();
	}
}

int32_t CardAttackContext::get_total_damage() const
{
	return (this->attacker->get_damage() + this->extra_damage) * this->damage_modifier;
}

BattleAction::AttackType CardAttackContext::result() const
{
	if (!this->updated)
		throw Exception("Attack context result requested without update call");

	return this->attack_type;
}

bool CardAttackContext::is_possible() const
{
	return !this->forbidden;
}

bool CardAttackContext::is_blocked() const
{
	return this->blocked;
}

bool CardAttackContext::is_success() const
{
	switch (this->result())
	{
		case BattleAction::AttackType::ATTACK_DODGE:
		case BattleAction::AttackType::ATTACK_FAILED:
			return false;
		case BattleAction::AttackType::ATTACK_CRITICAL:
		case BattleAction::AttackType::ATTACK_NORMAL:
			return true;
	}

	logger()->warning("Unknown attack result %u", enum_unwrap(this->attack_type));
	throw Exception("Unknown attack result");
}

void CardAttackContext::forbid()
{
	this->forbidden = true;
	this->attack_type = BattleAction::AttackType::ATTACK_FAILED;

	this->updated = true;
}

void CardAttackContext::block()
{
	this->blocked = true;
	this->attack_type = BattleAction::AttackType::ATTACK_FAILED;

	this->updated = true;
}