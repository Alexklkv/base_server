#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class BlockAttackEffect final : public CardAttackEffect, public NegativeEffect
{
protected:
	virtual bool on_attacker_before(CardAttackContext &ctx) const override;

public:
	BlockAttackEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);

	bool is_forbid_action(bool is_target_summoner) const override;
};