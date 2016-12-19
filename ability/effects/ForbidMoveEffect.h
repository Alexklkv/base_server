#pragma once

#include "ability/effects/basic/CardMoveEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class ForbidMoveEffect : public CardMoveEffect, public NegativeEffect
{
protected:
	virtual bool on_before_move(CardMoveContext &ctx) const override;

public:
	ForbidMoveEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};