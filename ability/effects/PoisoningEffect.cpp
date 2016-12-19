#include "PoisoningEffect.h"

#include "BattleField.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

PoisoningEffect::PoisoningEffect(uint32_t id, ability::Type type, const Calculator *damage, const policy_factory_t &factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, factory), calculator(damage)
{}

PoisoningEffect::~PoisoningEffect()
{
	delete this->calculator;
}

bool PoisoningEffect::on_self_round_start(RoundContext &ctx) const
{
	if (ctx.owner->is_dead() || !ctx.owner->is_card())
		return false;

	auto damage = this->calculator->get(ctx.owner->get_health());
	ctx.field->damage(ctx.owner, ctx.owner, damage);
	ctx.log->effect(ctx.owner.get(), ctx.owner.get(), this, DataPacker().pack(ability::Action::ATTACK, (uint16_t)damage));

	return true;
}