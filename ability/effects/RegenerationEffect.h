#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"

class RegenerationEffect : public RoundEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	virtual bool on_self_round_start(RoundContext &ctx) const override;

public:
	RegenerationEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy);
	~RegenerationEffect();
};