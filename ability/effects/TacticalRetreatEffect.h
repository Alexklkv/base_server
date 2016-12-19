#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class TacticalRetreatEffect : public CardAttackEffect, public PositiveEffect
{
protected:
	virtual bool on_target_before(CardAttackContext &ctx) const override;

public:
	TacticalRetreatEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};
