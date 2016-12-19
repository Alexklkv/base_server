#pragma once

#include "EffectsApplicatorAbility.h"		// EffectsApplicatorAbility
#include "TargetingAbility.h"			// TargetingAbility

#include <initializer_list>

class EffectsAbility : public EffectsApplicatorAbility, public TargetingAbility
{
public:
	EffectsAbility(ability::Type type, const AbilityTargeting::target_picker_t &picker, std::initializer_list<const BattleEffect*> effects);
};