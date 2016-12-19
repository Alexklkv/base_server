#include "OnResponseEffect.h"

#include "BattleField.h"
#include "CardHandler.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

OnResponseEffect::OnResponseEffect(uint32_t id, ability::Type type, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), effects(effects), mask(mask)
{}

OnResponseEffect::~OnResponseEffect()
{
	for (auto &effect : this->effects)
		delete effect;
}

bool OnResponseEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.is_response || !this->mask.compare_card(ctx.target->get_card()))
		return false;

	BattleAction::sources_t sources;
	sources.push_back(ctx.attacker->object_id());

	BattleAction::targets_t targets;
	bool result = true;

	for (auto &effect : this->effects)
		result = ctx.field->add_effect(ctx.attacker, ctx.target, effect, targets) || result;

	if (result)
		ctx.log->effect(std::move(sources), std::move(targets), this->effects.front()->get_ability());

	return result;
}