#include "ExtraDamageOnAttackEffect.h"

#include "BattleField.h"
#include "DataPacker.h"
#include "Log.h"
#include "Random.h"

#include "battle/RoundActionsLog.h"

ExtraDamageOnAttackEffect::ExtraDamageOnAttackEffect(uint32_t id, ability::Type type, const policy_factory_t &policy, uint8_t probability, const damage_calculator_t &calculator):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator), probability(probability)
{}

bool ExtraDamageOnAttackEffect::on_attacker_after(CardAttackContext &ctx) const
{
	if (ctx.target->is_dead())
		return false;

	if (!Random::chance(this->probability))
	{
		logger()->debug("Dice failed for extra damage effect");
		return false;
	}

	auto damage = this->calculator(ctx);
	if (damage == 0)
		return false;

	ctx.field->damage(ctx.attacker, ctx.target, damage);
	ctx.log->effect(ctx.attacker.get(), ctx.target.get(), this, DataPacker().pack(ability::Action::ATTACK, (uint32_t)damage));

	return true;
}

ExtraDamageOnAttackEffect::damage_calculator_t ExtraDamageOnAttackEffect::constant(uint32_t value)
{
	return [value] (const CardAttackContext&) {
		return value;
	};
}

ExtraDamageOnAttackEffect::damage_calculator_t ExtraDamageOnAttackEffect::target_health_percent(uint8_t value)
{
	return [value] (const CardAttackContext &ctx) {
		return ctx.target->get_max_health() * value / 100;
	};
}