#include "OnAttackEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Random.h"
#include "Sharps.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

#include "params.h"

OnAttackEffect::OnAttackEffect(uint32_t id, ability::Type type, uint8_t probability, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), effects(effects), mask(mask), probability(probability)
{}

OnAttackEffect::~OnAttackEffect()
{
	for (auto &effect : this->effects)
		delete effect;
}

bool OnAttackEffect::on_attacker_after(CardAttackContext &ctx) const
{
	uint8_t extra = Sharps::get_sharp_times(this->get_ability(), ctx.attacker->get_card());
	uint8_t total_chance = this->probability * extra;
	if (!Random::chance(total_chance))
		return false;
	if (!this->mask.compare_card(ctx.target->get_card()) && this->get_ability() != ability::CARD_ICE_TOUCH)
		return false;
	if (this->mask.compare_card(ctx.target->get_card()) && this->get_ability() == ability::CARD_ICE_TOUCH)
		return false;

	BattleAction::sources_t sources;
	sources.push_back(ctx.attacker->object_id());

	BattleAction::targets_t targets;
	bool result = false;

	for (auto &effect : this->effects)
		result = ctx.field->add_effect(ctx.attacker, ctx.target, effect, targets) || result;

	ctx.log->effect(std::move(sources), std::move(targets), this->effects.front()->get_ability());

	return result;
}

bool OnAttackEffect::on_before_application(StatsContext &) const
{
	return false;
}