#include "IfritEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

IfritEffect::IfritEffect(uint32_t id, ability::Type type, CardMask mask, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), mask(mask)
{}

bool IfritEffect::on_target_before(CardAttackContext& ctx) const
{
	if (!ctx.attacker->is_card() || !this->mask.compare_card(ctx.attacker->get_card()))
		return false;

	uint16_t heal = ctx.get_total_damage();

	ctx.field->heal(ctx.attacker, ctx.target, heal);
	ctx.field->write_effect(this, ctx.attacker, {{ctx.target->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	ctx.forbid();

	return true;
}

bool IfritEffect::on_before_application(StatsContext& ) const
{
	return false;
}