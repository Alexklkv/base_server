#pragma once

#include "basic/PositiveEffect.h"
#include "basic/CardMoveEffect.h"
#include "basic/StatsEffect.h"

#include "CardMask.h"

class EarthThremorsEffect final : public CardMoveEffect, public virtual StatsEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;

	const CardMask mask;
	const Calculator *calculator;

protected:
	bool on_after_move(CardMoveContext &ctx) const override;
	bool on_before_application(StatsContext &ctx) const override;

public:
	EarthThremorsEffect(uint32_t id, ability::Type type, CardMask mask, Calculator *calculator, const policy_factory_t &policy);
	~EarthThremorsEffect();
};