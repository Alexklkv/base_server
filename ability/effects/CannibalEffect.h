#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class CannibalEffect : public CardAttackEffect, public PositiveEffect
{
protected:
	bool on_attacker_after(CardAttackContext &ctx) const override;
	bool on_target_after(CardAttackContext &ctx) const override;
public:
	CannibalEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};