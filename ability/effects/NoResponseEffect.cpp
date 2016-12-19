#include "NoResponseEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"

#include "battle/RoundActionsLog.h"

NoResponseEffect::NoResponseEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::BLOCK_IN_RESPONSE, 0, policy_factory)
{}

bool NoResponseEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.attacker->is_card() || !ctx.is_response)
		return false;

	ctx.forbid();
	ctx.field->write_effect(this, ctx.target, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(0), ability::Duration::INFINITE)}});

	return true;
}