#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"
#include "basic/StatsEffect.h"

class HealerEffect final : public virtual RoundEffect, public virtual StatsEffect, public PositiveEffect
{
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator;

	combatant_ptr_t get_min_health_card(combatant_ptr_t &owner) const;

protected:
	bool on_self_round_start(RoundContext &ctx) const override;
	bool on_before_application(StatsContext &ctx) const override;

public:
	HealerEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy);
	~HealerEffect();
};