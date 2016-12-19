#pragma once

#include "basic/PositiveEffect.h"
#include "basic/StatsEffect.h"

#include "misc.h"

class ExtraCriticalEffect : public StatsEffect, public PositiveEffect
{
private:
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	bool on_before_application(StatsContext &ctx) const override;
	bool on_after_removal(StatsContext &ctx) const override;

public:
	ExtraCriticalEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy_factory);
	~ExtraCriticalEffect();
};