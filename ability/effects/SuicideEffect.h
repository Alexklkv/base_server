#pragma once

#include "CardMask.h"

#include "basic/CardAttackEffect.h"
#include "basic/NegativeEffect.h"

class SuicideEffect final : public CardAttackEffect, public NegativeEffect
{
protected:
	virtual bool on_attacker_after(CardAttackContext &ctx) const override;

public:
	SuicideEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};