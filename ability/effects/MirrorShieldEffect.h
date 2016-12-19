#pragma once

#include "CardMask.h"

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class MirrorShieldEffect : public CardAttackEffect, public PositiveEffect
{
private:
	using Calculator = calculators::ValueCalculator;

	const CardMask mask;
	const Calculator *calculator;

protected:
	virtual bool on_target_after(CardAttackContext &ctx) const override;

public:
	MirrorShieldEffect(uint32_t id, ability::Type type, CardMask mask, const Calculator *calculator, const policy_factory_t &policy);
	~MirrorShieldEffect();
};