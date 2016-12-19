#pragma once

#include "basic/CardAttackEffect.h"
#include "basic/PositiveEffect.h"

class NecromancyEffect final : public virtual CardAttackEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	bool on_target_after(CardAttackContext &ctx) const override;

public:
	NecromancyEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy);
	~NecromancyEffect();
};