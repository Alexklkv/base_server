#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class BattleEffect;

class ProvocationEffect final : public CardAttackEffect, public NegativeEffect
{
protected:
	bool on_attacker_before(CardAttackContext &ctx) const override;
public:
	ProvocationEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};