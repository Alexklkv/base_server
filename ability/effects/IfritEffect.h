#pragma once

#include "CardMask.h"

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"
#include "ability/effects/basic/StatsEffect.h"

class IfritEffect final : public virtual CardAttackEffect, public virtual StatsEffect, public PositiveEffect
{
private:
	const CardMask mask;

	bool on_target_before(CardAttackContext &ctx) const override;
	bool on_before_application(StatsContext &ctx) const override;

public:
	IfritEffect(uint32_t id, ability::Type type, CardMask mask, const policy_factory_t &policy);
};