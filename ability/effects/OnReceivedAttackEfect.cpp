#include "OnReceivedAttackEfect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Random.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

OnReceivedAttackEfect::OnReceivedAttackEfect(uint32_t id, ability::Type type, uint8_t probability, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), effects(effects), mask(mask), probability(probability)
{}

OnReceivedAttackEfect::~OnReceivedAttackEfect()
{
	for (auto &effect : this->effects)
		delete effect;
}

bool OnReceivedAttackEfect::on_target_before(CardAttackContext &ctx) const
{
	if (!this->mask.compare_card(ctx.attacker->get_card()) || !Random::chance(this->probability))
		return false;

	BattleAction::sources_t sources;
	sources.push_back(ctx.target->object_id());

	BattleAction::targets_t targets;
	bool result = true;

	for (auto &effect : this->effects)
		result = ctx.field->add_effect(ctx.target, ctx.attacker, effect, targets) || result;

	return result;
}

bool OnReceivedAttackEfect::on_before_application(StatsContext &) const
{
	return false;
}