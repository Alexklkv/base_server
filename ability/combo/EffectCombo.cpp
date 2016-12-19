#include "EffectCombo.h"

EffectCombo::EffectCombo(ability::Type type, const picker_t &picker, std::initializer_list<ability::Type> predecessors, std::initializer_list<const BattleEffect*> effects):
	Combo(type, predecessors), EffectApplyingCombo(effects), TargetedCombo(picker)
{}