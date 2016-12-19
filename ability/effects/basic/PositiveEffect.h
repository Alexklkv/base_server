#pragma once

#include "BattleEffect.h"

class PositiveEffect : public virtual BattleEffect
{
public:
	virtual bool is_negative_for(const combatant_ptr_t &target) const override;
};