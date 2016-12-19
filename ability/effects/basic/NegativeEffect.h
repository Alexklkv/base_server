#pragma once

#include "BattleEffect.h"

class NegativeEffect : public virtual BattleEffect
{
public:
	virtual bool is_negative_for(const combatant_ptr_t &target) const override;
};