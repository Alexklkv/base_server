#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"

class InsanityEffect : public RoundEffect, public PositiveEffect
{
protected:
	virtual bool on_self_round_start(RoundContext &ctx) const override;

public:
	InsanityEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};