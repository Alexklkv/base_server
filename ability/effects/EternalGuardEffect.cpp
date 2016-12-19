#include "EternalGuardEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

#include "misc.h"

EternalGuardEffect::EternalGuardEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::BLOCK_PASSIVE_USE, 0, policy_factory)
{}

bool EternalGuardEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.attacker->is_card())
		return false;

	if (ctx.is_response)
		return true;

	ctx.forbid();
	ctx.field->write_effect(this, ctx.target, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(0), ability::Duration::INFINITE)}});

	return true;
}

bool EternalGuardEffect::on_before_application(StatsContext &) const
{
	return false;
}