#include "EffectsApplicatorAbility.h"

#include "BattleField.h"

#include "ability/effects/basic/BattleEffect.h"

EffectsApplicatorAbility::EffectsApplicatorAbility(std::initializer_list<const BattleEffect*> effects):
	effects(effects)
{}

EffectsApplicatorAbility::~EffectsApplicatorAbility()
{
	for (const BattleEffect *effect : this->effects)
		delete effect;
}

void EffectsApplicatorAbility::do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const
{
	for (auto effect : this->effects)
		field->add_effect(caster, target, effect, log);
}