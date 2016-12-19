#pragma once

#include "ability/effects/basic/CardPlacementEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class WrongSummonEffect : public CardPlacementEffect, public NegativeEffect
{
protected:
	virtual bool on_before_placement(CardAddContext &ctx) const override;

public:
	WrongSummonEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};