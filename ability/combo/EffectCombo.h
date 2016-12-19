#pragma once

#include "EffectApplyingCombo.h"
#include "TargetedCombo.h"

class EffectCombo : public EffectApplyingCombo, public TargetedCombo
{
public:
	EffectCombo(ability::Type type, const picker_t &picker, std::initializer_list<ability::Type> predecessors, std::initializer_list<const BattleEffect*> effects);
};