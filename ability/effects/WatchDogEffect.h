#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class WatchDogEffect final : public CardAttackEffect, public NegativeEffect
{
private:
	bool on_attacker_before(CardAttackContext &ctx) const override;
public:
	WatchDogEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};