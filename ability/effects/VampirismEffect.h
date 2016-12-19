#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class VampirismEffect final : public CardAttackEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	bool on_attacker_after(CardAttackContext &ctx) const override;

public:
	VampirismEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy);
	~VampirismEffect();
};