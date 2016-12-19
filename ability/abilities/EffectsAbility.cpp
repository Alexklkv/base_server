#include "EffectsAbility.h"

EffectsAbility::EffectsAbility(ability::Type type, const AbilityTargeting::target_picker_t &picker, std::initializer_list<const BattleEffect*> effects):
	Ability(type), EffectsApplicatorAbility(effects), TargetingAbility(picker)
{}