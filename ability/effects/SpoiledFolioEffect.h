#pragma once

#include "ability/effects/basic/CardPlacementEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class SpoiledFolioEffect : public CardPlacementEffect, public NegativeEffect
{
public:
	SpoiledFolioEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);

	virtual bool on_before_placement(CardAddContext &ctx) const override;
};