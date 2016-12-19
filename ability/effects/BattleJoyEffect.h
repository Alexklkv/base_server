#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"
#include "ability/effects/basic/StatsEffect.h"

class BattleJoyEffect final : public virtual CardAttackEffect, public virtual StatsEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

protected:
	bool on_attacker_after(CardAttackContext &ctx) const override;
	bool on_before_application(StatsContext &ctx) const override;

public:
	BattleJoyEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy);
	~BattleJoyEffect();
};