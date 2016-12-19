#pragma once

#include "CardMask.h"

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class BattleEffect;

class OnResponseEffect final: public CardAttackEffect, public NegativeEffect
{
private:
	std::list<BattleEffect*> effects;
	const CardMask mask;

protected:
	bool on_attacker_before(CardAttackContext &ctx) const override;

public:
	OnResponseEffect(uint32_t id, ability::Type type, CardMask mask, std::initializer_list<BattleEffect*> effects, const policy_factory_t &policy);
	virtual ~OnResponseEffect();
};