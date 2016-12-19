#pragma once

#include "basic/PositiveEffect.h"
#include "basic/StatsEffect.h"

#include "misc.h"

class ExtraDamageEffect : public StatsEffect
{
protected:
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

	mutable bool is_negative;
	mutable bool use_full_value;

	virtual bool on_before_application(StatsContext &ctx) const override;
	virtual bool on_after_removal(StatsContext &ctx) const override;

public:
	ExtraDamageEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy_factory, bool use_full_value = false);
	virtual ~ExtraDamageEffect();

	bool is_negative_for(const combatant_ptr_t &target) const override;
};