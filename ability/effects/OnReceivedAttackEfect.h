#pragma once

#include "CardMask.h"

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"
#include "ability/effects/basic/StatsEffect.h"

class BattleEffect;

class OnReceivedAttackEfect : public virtual CardAttackEffect, public virtual StatsEffect, public NegativeEffect
{
private:
	std::list<BattleEffect*> effects;
	const CardMask mask;
	const uint8_t probability;

protected:
	virtual bool on_target_before(CardAttackContext &ctx) const override;
	virtual bool on_before_application(StatsContext &ctx) const override;

public:
	OnReceivedAttackEfect(uint32_t id, ability::Type type, uint8_t probability, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy);
	virtual ~OnReceivedAttackEfect();
};