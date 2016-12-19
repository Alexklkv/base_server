#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class ExtraDamageOnAttackEffect : public CardAttackEffect, public PositiveEffect
{
public:
	typedef std::function<uint32_t(const CardAttackContext&)> damage_calculator_t;

private:
	damage_calculator_t calculator;
	const uint8_t probability;

protected:
	virtual bool on_attacker_after(CardAttackContext &ctx) const override;

public:
	ExtraDamageOnAttackEffect(uint32_t id, ability::Type type, const policy_factory_t &policy, uint8_t probability, const damage_calculator_t &calculator);

	static damage_calculator_t constant(uint32_t value);
	static damage_calculator_t target_health_percent(uint8_t value);
};