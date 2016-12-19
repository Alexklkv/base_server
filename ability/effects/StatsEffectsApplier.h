#pragma once

#include "CardMask.h"

#include "ability/effects/basic/PositiveEffect.h"
#include "ability/effects/basic/StatsEffect.h"

class BattleEffect;

class StatsEffectsApplier final : public StatsEffect, public PositiveEffect
{
private:
	std::list<BattleEffect*> effects;
	const CardMask mask;

protected:
	bool on_before_application(StatsContext &ctx) const override;
	bool on_after_removal(StatsContext &ctx) const override;
public:
	StatsEffectsApplier(uint32_t id, ability::Type type, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy);
	~StatsEffectsApplier();
};