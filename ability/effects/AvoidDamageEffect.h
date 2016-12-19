#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class AvoidDamageEffect : public CardAttackEffect, public PositiveEffect
{
	const uint8_t probability;

public:
	AvoidDamageEffect(uint32_t id, ability::Type type, uint8_t probability, const policy_factory_t &policy_factory);

	virtual bool on_target_before(CardAttackContext &ctx) const override;
};