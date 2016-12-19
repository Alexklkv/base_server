#pragma once

#include "ability/Data.h"
#include "battle/CardAddContext.h"
#include "battle/CardAttackContext.h"
#include "battle/CardMoveContext.h"
#include "battle/CardSpellContext.h"
#include "battle/Combatant.h"
#include "battle/RoundContext.h"
#include "battle/StatsContext.h"

#include "enums.h"

#include <functional>

class ActiveEffects;
class RetentionPolicy;

class BattleEffect
{
public:
	typedef std::function<RetentionPolicy*()> policy_factory_t;

private:
	const uint32_t id;
	const ability::Type ability_type;
	const ability::Modifier effect;
	const uint32_t priority;
	const policy_factory_t policy_factory;

public:
	static policy_factory_t policy_infinite();
	static policy_factory_t policy_placement();
	static policy_factory_t policy_combo();
	static policy_factory_t policy_turn(uint32_t turns);
	static policy_factory_t policy_actions(uint32_t actions);

	virtual ~BattleEffect() {}

	uint32_t get_id() const;
	ability::Type get_ability() const;
	ability::Modifier get_effect() const;
	uint32_t get_priority() const;
	RetentionPolicy* create_policy() const;

	// Some effects can be both negative and positive depending on application
	// context. For example, poisoning behaves as healing for some classes
	// of creatures making it positive.
	virtual bool is_negative_for(const combatant_ptr_t &target) const = 0;
	virtual bool is_forbid_action(bool is_target_summoner) const;

	// Attack
	virtual bool attacker_before(CardAttackContext &ctx) const;
	virtual bool attacker_after(CardAttackContext &ctx) const;
	virtual bool target_before(CardAttackContext &ctx) const;
	virtual bool target_after(CardAttackContext &ctx) const;

	// Spell
	virtual bool before_caster(CardSpellContext &ctx) const;
	virtual bool after_caster(CardSpellContext &ctx) const;
	virtual bool before_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const;
	virtual bool after_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const;

	// Move
	virtual bool before_move(CardMoveContext &ctx) const;
	virtual bool after_move(CardMoveContext &ctx) const;

	// Placement
	virtual bool before_placement(CardAddContext &ctx) const;
	virtual bool after_placement(CardAddContext &ctx) const;

	// Round
	virtual bool self_round_start(RoundContext &ctx) const;
	virtual bool self_round_end(RoundContext &ctx) const;
	virtual bool other_round_start(RoundContext &ctx) const;
	virtual bool other_round_end(RoundContext &ctx) const;

	// Lifetime
	virtual bool before_application(StatsContext &ctx) const;
	virtual bool after_removal(StatsContext &ctx) const;

protected:
	[[noreturn]] BattleEffect();
	BattleEffect(uint32_t id, ability::Type type, ability::Modifier effect, uint32_t priority, const policy_factory_t &policy_factory);
};