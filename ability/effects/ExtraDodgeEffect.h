#pragma once

#include "basic/PositiveEffect.h"
#include "basic/StatsEffect.h"

#include "misc.h"

class ExtraDodgeEffect : public StatsEffect, public PositiveEffect
{
protected:
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

	virtual bool on_before_application(StatsContext &ctx) const override;
	virtual bool on_after_removal(StatsContext &ctx) const override;

public:
	ExtraDodgeEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy_factory);
	~ExtraDodgeEffect();
};