#include "BlockAttackEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

BlockAttackEffect::BlockAttackEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::BLOCK_IN_RESPONSE, 0, policy_factory)
{}

bool BlockAttackEffect::is_forbid_action(bool) const
{
	return true;
}

bool BlockAttackEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.attacker->is_card())
		return false;

	if (this->is_forbid_action(ctx.target->is_summoner()))
		ctx.forbid();

	ctx.field->write_effect(this, ctx.target, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(0), ability::Duration::INFINITE)}});

	return true;
}