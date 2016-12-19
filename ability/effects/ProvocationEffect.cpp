#include "ProvocationEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

ProvocationEffect::ProvocationEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::PROVOCATION, 0, policy)
{}

bool ProvocationEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.attacker->is_card())
		return false;

	return true;
}