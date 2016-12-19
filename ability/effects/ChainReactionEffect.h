#pragma once

#include "basic/CardAttackEffect.h"
#include "basic/PositiveEffect.h"

class ChainReactionEffect : public CardAttackEffect, public PositiveEffect
{
private:
	bool on_attacker_after(CardAttackContext &ctx) const override;

public:
	ChainReactionEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};
