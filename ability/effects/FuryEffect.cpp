#include "FuryEffect.h"

#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/Combatant.h"

FuryEffect::FuryEffect(uint32_t id, ability::Type type, const Calculator *calculator_health, const Calculator *calculator, const policy_factory_t &policy_factory) :
	BattleEffect(id, type, ability::Modifier::MODIFY_ATTACK, 0, policy_factory), ExtraDamageEffect(id, type, calculator, policy_factory), calculator_health(calculator_health)
{}

FuryEffect::~FuryEffect()
{
	delete this->calculator_health;
}

bool FuryEffect::on_before_application(StatsContext&) const
{
	return false;
}

bool FuryEffect::on_attacker_before(CardAttackContext &ctx) const
{
	auto combatant = ctx.attacker;
	if (!combatant->is_card())
		return false;

	uint16_t min_health = this->calculator_health->get(combatant->get_max_health());

	uint16_t health = combatant->get_health();
	if (health >= min_health)
		return false;

	StatsContext stats_ctx(ctx.attacker, ctx.field, ctx.targets_log);
	return ExtraDamageEffect::on_before_application(stats_ctx);
}