#pragma once

#include "basic/CardAttackEffect.h"
#include "ExtraDamageEffect.h"

#include "misc.h"

class FuryEffect final : public virtual ExtraDamageEffect, public CardAttackEffect
{
private:
	using Calculator = calculators::ValueCalculator;
	const Calculator *calculator_health;

protected:
	bool on_before_application(StatsContext &ctx) const override;
	bool on_attacker_before(CardAttackContext &ctx) const override;

public:
	FuryEffect(uint32_t id, ability::Type type, const Calculator *calculator_health, const Calculator *calculator, const policy_factory_t &policy_factory);
	~FuryEffect();
};