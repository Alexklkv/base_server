#pragma once

#include "basic/BattleEffect.h"
#include "basic/NegativeEffect.h"

class WarFogEffect : public NegativeEffect
{
public:
	WarFogEffect(uint32_t id, ability::Type type, const policy_factory_t &factory);
};