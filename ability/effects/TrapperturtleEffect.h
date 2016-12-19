#pragma once

#include "basic/PositiveEffect.h"
#include "basic/RoundEffect.h"

class TrapperturtleEffect : public RoundEffect, public PositiveEffect
{
public:
	TrapperturtleEffect(uint32_t id, ability::Type type, const policy_factory_t &policy);
};