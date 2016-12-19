#pragma once

#include "ability/effects/basic/PositiveEffect.h"
#include "ability/effects/basic/StatsEffect.h"

class RevengeEffect final : public StatsEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	bool on_after_removal(StatsContext &ctx) const override;

public:
	RevengeEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy_factory);
	~RevengeEffect();
};