#pragma once

#include "ability/effects/basic/NegativeEffect.h"
#include "ability/effects/basic/StatsEffect.h"

class AttackMoveEffect : public StatsEffect, public NegativeEffect
{
protected:
	virtual bool on_before_application(StatsContext &ctx) const override;

public:
	AttackMoveEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};