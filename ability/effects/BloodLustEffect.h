#pragma once

#include "basic/NegativeEffect.h"
#include "basic/RoundEffect.h"

class BloodLustEffect final : public RoundEffect, public NegativeEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	virtual bool on_self_round_end(RoundContext &ctx) const override;

public:
	BloodLustEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy);
	~BloodLustEffect();
};