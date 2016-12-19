#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"
#include "ability/effects/basic/StatsEffect.h"
#include "basic/StatsEffect.h"

class EternalGuardEffect final : public CardAttackEffect, public StatsEffect, public NegativeEffect
{
protected:
	virtual bool on_attacker_before(CardAttackContext &ctx) const override;
	virtual bool on_before_application(StatsContext &ctx) const override;

public:
	EternalGuardEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};