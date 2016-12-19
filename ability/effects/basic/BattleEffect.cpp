#include "BattleEffect.h"

#include "BattleField.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Log.h"

#include "ability/effects/retention/ActionsRetentionPolicy.h"
#include "ability/effects/retention/ComboRetentionPolicy.h"
#include "ability/effects/retention/InfiniteRetentionPolicy.h"
#include "ability/effects/retention/PlacementRetentionPolicy.h"
#include "ability/effects/retention/TurnsRetentionPolicy.h"
#include "battle/ActiveEffects.h"
#include "battle/RoundActionsLog.h"

BattleEffect::BattleEffect():
	id(0), ability_type(ability::Type::NO_ABILITY), effect(ability::Modifier::NONE_MODIFIER), priority(0), policy_factory(policy_infinite())
{
	throw Exception("BattleEffect is a virtual base class");
}

BattleEffect::BattleEffect(uint32_t id, ability::Type type, ability::Modifier effect, uint32_t priority, const policy_factory_t &policy_factory):
	id(id), ability_type(type), effect(effect), priority(priority), policy_factory(policy_factory)
{}

BattleEffect::policy_factory_t BattleEffect::policy_infinite()
{
	return [] () {
		return new InfiniteRetentionPolicy();
	};
}

BattleEffect::policy_factory_t BattleEffect::policy_placement()
{
	return [] () {
		return new PlacementRetentionPolicy();
	};
}

BattleEffect::policy_factory_t BattleEffect::policy_combo()
{
	return [] () {
		return new ComboRetentionPolicy();
	};
}

BattleEffect::policy_factory_t BattleEffect::policy_actions(uint32_t actions)
{
	return [actions] () {
		return new ActionsRetentionPolicy(actions);
	};
}

BattleEffect::policy_factory_t BattleEffect::policy_turn(uint32_t turns)
{
	return [turns] () {
		return new TurnsRetentionPolicy(turns);
	};
}

uint32_t BattleEffect::get_id() const
{
	return this->id;
}

ability::Type BattleEffect::get_ability() const
{
	return this->ability_type;
}

ability::Modifier BattleEffect::get_effect() const
{
	return this->effect;
}

uint32_t BattleEffect::get_priority() const
{
	return this->priority;
}

RetentionPolicy* BattleEffect::create_policy() const
{
	return this->policy_factory();
}

bool BattleEffect::is_forbid_action(bool is_target_summoner) const
{
	if (is_target_summoner && this->ability_type == ability::Type::CARD_WATCH_DOG)
		return true;

	return false;
}

bool BattleEffect::attacker_before(CardAttackContext&) const
{
	return false;
}

bool BattleEffect::attacker_after(CardAttackContext&) const
{
	return false;
}

bool BattleEffect::target_before(CardAttackContext&) const
{
	return false;
}

bool BattleEffect::target_after(CardAttackContext&) const
{
	return false;
}

bool BattleEffect::before_caster(CardSpellContext&) const
{
	return false;
}

bool BattleEffect::after_caster(CardSpellContext&) const
{
	return false;
}

bool BattleEffect::before_target(CardSpellContext&, combatant_ptr_t&) const
{
	return false;
}

bool BattleEffect::after_target(CardSpellContext&, combatant_ptr_t&) const
{
	return false;
}

bool BattleEffect::before_move(CardMoveContext&) const
{
	return false;
}

bool BattleEffect::after_move(CardMoveContext&) const
{
	return false;
}

bool BattleEffect::before_placement(CardAddContext&) const
{
	return false;
}

bool BattleEffect::after_placement(CardAddContext&) const
{
	return false;
}

bool BattleEffect::self_round_start(RoundContext&) const
{
	return false;
}

bool BattleEffect::self_round_end(RoundContext&) const
{
	return false;
}

bool BattleEffect::other_round_start(RoundContext&) const
{
	return false;
}

bool BattleEffect::other_round_end(RoundContext&) const
{
	return false;
}

bool BattleEffect::before_application(StatsContext &ctx) const
{
	ability::Duration duration = ability::Duration::TEMPORARY;
	auto policy = this->create_policy();
	if (policy->type == RetentionPolicy::INFINITE)
		duration = ability::Duration::INFINITE;
	delete policy;

	if (ctx.caster == nullptr)
		return true;

	if (!ctx.owner->get_active_effects()->add(ctx.caster->object_id(), this, ctx.caster))
		return false;

	ctx.targets_log.emplace_back(ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (uint16_t)0, duration));
	ctx.field->write_effect(this, ctx.caster, std::move(ctx.targets_log));

	return true;
}

bool BattleEffect::after_removal(StatsContext &ctx) const
{
	ctx.log->effect_remove(ctx.owner.get(), this->get_ability(), this->get_effect());
	return true;
}