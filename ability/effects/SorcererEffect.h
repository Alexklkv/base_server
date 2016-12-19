#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"
#include "basic/StatsEffect.h"

class SorcererEffect final : public virtual RoundEffect, public virtual StatsEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	bool on_self_round_start(RoundContext &ctx) const override;
	bool on_before_application(StatsContext &ctx) const override;

public:
	SorcererEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy);
	~SorcererEffect();
};