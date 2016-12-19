#include "SuicideEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

#include "types.h"

SuicideEffect::SuicideEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy)
{}

bool SuicideEffect::on_attacker_after(CardAttackContext &ctx) const
{
	auto combatant = ctx.attacker;
	if (!combatant->is_card())
		return false;

	if (combatant->is_dead())
		return false;

	if (ctx.is_response)
		return false;

	uint16_t damage = combatant->get_health();
	ctx.field->damage(combatant, combatant, damage);
	ctx.log->attack(BattleAction::AttackType::ATTACK_NORMAL, combatant.get(), combatant.get(), damage);

	return true;
}
