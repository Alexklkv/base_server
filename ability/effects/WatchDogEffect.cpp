#include "WatchDogEffect.h"

#include "BattleField.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

WatchDogEffect::WatchDogEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::BLOCK_IN_RESPONSE, 0, policy_factory)
{}

bool WatchDogEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.target->is_summoner())
		return false;

	ctx.forbid();
	ctx.field->write_effect(this, ctx.target, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(0), ability::Duration::INFINITE)}});

	return true;
}