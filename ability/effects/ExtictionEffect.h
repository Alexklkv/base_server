#pragma once

#include "basic/RoundEffect.h"
#include "basic/PositiveEffect.h"

#include "misc.h"

class ExtictionEffect : public RoundEffect, public PositiveEffect
{
protected:
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

	bool on_self_round_start(RoundContext &ctx) const override;

public:
	ExtictionEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy_factory);
	virtual ~ExtictionEffect();
};