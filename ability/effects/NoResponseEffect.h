#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class NoResponseEffect : public CardAttackEffect, public NegativeEffect
{
protected:
	virtual bool on_attacker_before(CardAttackContext &ctx) const override;

public:
	NoResponseEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};