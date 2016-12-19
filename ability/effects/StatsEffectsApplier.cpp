#include "StatsEffectsApplier.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Log.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

StatsEffectsApplier::StatsEffectsApplier(uint32_t id, ability::Type type, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), effects(effects), mask(mask)
{}

StatsEffectsApplier::~StatsEffectsApplier()
{
	for (auto &effect : this->effects)
		delete effect;
}

bool StatsEffectsApplier::on_before_application(StatsContext &ctx) const
{
	if (ctx.owner->is_card() && !this->mask.compare_card(ctx.owner->get_card()))
		return false;

	bool result = false;

	for (auto &effect : this->effects)
		result = effect->before_application(ctx) || result;

	if (result)
		ctx.field->write_effect(this, ctx.owner, std::move(ctx.targets_log));

	return result;
}

bool StatsEffectsApplier::on_after_removal(StatsContext &ctx) const
{
	bool result = false;

	for (auto rit = this->effects.rbegin(); rit != this->effects.rend(); ++rit)
		result = (*rit)->after_removal(ctx) || result;

	return result;
}