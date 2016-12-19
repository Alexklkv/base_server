#pragma once

#include "basic/NegativeEffect.h"
#include "basic/RoundEffect.h"

class SleepingEffect : public NegativeEffect, public RoundEffect
{
protected:
	virtual bool on_self_round_start(RoundContext& ctx) const override;

public:
	SleepingEffect(uint32_t id, ability::Type type, const policy_factory_t &factory);
};