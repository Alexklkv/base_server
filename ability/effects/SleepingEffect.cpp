#include "SleepingEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"

#include "battle/RoundActionsLog.h"

SleepingEffect::SleepingEffect(uint32_t id, ability::Type type, const policy_factory_t &factory):
	BattleEffect(id, type, ability::Modifier::SLEEP, 0, factory)
{}

bool SleepingEffect::on_self_round_start(RoundContext &ctx) const
{
	if (!ctx.owner->is_card())
		throw Exception("Non-card target supplied to Sleeping effect");

	if (ctx.owner->get_card()->used)
		return false;

	ctx.owner->get_card()->used = true;

	return true;
}