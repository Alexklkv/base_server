#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/PositiveEffect.h"

class CsaadGiftEffect final : public CardAttackEffect, public PositiveEffect
{
protected:
	bool on_target_after(CardAttackContext &ctx) const override;

public:
	CsaadGiftEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};