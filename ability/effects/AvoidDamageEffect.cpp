#include "AvoidDamageEffect.h"

#include "DataPacker.h"
#include "Log.h"
#include "Random.h"

#include "battle/RoundActionsLog.h"

AvoidDamageEffect::AvoidDamageEffect(uint32_t id, ability::Type type, uint8_t probability, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory), probability(probability)
{}

bool AvoidDamageEffect::on_target_before(CardAttackContext &ctx) const
{
	if (!Random::chance(this->probability))
	{
		logger()->debug("Damage avoiding effect dice failed");
		return false;
	}

	ctx.block();
	ctx.log->effect(ctx.target.get(), this);

	return true;
}