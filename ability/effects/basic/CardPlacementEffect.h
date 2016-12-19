#pragma once

#include "BattleEffect.h"

class CardPlacementEffect : public virtual BattleEffect
{
protected:
	virtual bool on_before_placement(CardAddContext &ctx) const;
	virtual bool on_after_placement(CardAddContext &ctx) const;

public:
	virtual ~CardPlacementEffect();

	virtual bool before_placement(CardAddContext &ctx) const override;
	virtual bool after_placement(CardAddContext &ctx) const override;
};