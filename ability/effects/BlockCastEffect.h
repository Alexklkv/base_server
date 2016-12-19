#pragma once

#include "ability/effects/basic/CardAttackEffect.h"
#include "ability/effects/basic/NegativeEffect.h"

class BlockCastEffect final : public NegativeEffect
{
public:
	BlockCastEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};