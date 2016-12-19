#pragma once

#include "basic/NegativeEffect.h"
#include "basic/RoundEffect.h"

#include "misc.h"

class ParasiteEffect : public NegativeEffect, public RoundEffect
{
	using Calculator = calculators::ValueCalculator;

	const Calculator *calculator;

protected:
	virtual bool on_self_round_start(RoundContext &ctx) const override;

public:
	ParasiteEffect(uint32_t id, ability::Type type, const Calculator *damage, const policy_factory_t &factory);
	~ParasiteEffect();
};