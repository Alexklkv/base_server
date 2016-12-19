#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"

class MeditationEffect final : public RoundEffect, public PositiveEffect
{
protected:
	bool on_other_round_end(RoundContext &ctx) const override;

public:
	MeditationEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};