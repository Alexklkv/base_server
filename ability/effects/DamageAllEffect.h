#pragma once

#include "CardMask.h"

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"
#include "basic/StatsEffect.h"

class DamageAllEffect final : public virtual RoundEffect, public virtual StatsEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;
	const CardMask mask;

protected:
	bool on_other_round_start(RoundContext &ctx) const override;
	bool on_before_application(StatsContext &ctx) const override;

public:
	DamageAllEffect(uint32_t id, ability::Type type, CardMask mask, Calculator *calculator, const policy_factory_t &policy);
	~DamageAllEffect();
};