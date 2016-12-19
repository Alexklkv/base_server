#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"

class EriylsSalvationEffect final : public RoundEffect, public PositiveEffect
{
protected:
	bool on_other_round_end(RoundContext &ctx) const override;

public:
	EriylsSalvationEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};