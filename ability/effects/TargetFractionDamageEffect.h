#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

#include "CardMask.h"
#include "misc.h"

class TargetFractionDamageEffect : public CardAttackEffect, public PositiveEffect
{
private:
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

	const CardMask mask;

protected:
	virtual bool on_attacker_before(CardAttackContext &ctx) const override;

public:
	TargetFractionDamageEffect(uint32_t id, ability::Type type, CardMask mask, const Calculator *calculator, const policy_factory_t &policy_factory);
	~TargetFractionDamageEffect();
};