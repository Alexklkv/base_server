#pragma once

#include "Ability.h"			// Ability

#include <initializer_list>

class BattleEffect;
class BattleField;

class EffectsApplicatorAbility : public virtual Ability
{
private:
	std::vector<const BattleEffect*> effects;

protected:
	explicit EffectsApplicatorAbility(std::initializer_list<const BattleEffect*> effects);

	virtual void do_apply(BattleAction::targets_t &log, combatant_ptr_t &caster, combatant_ptr_t &target, BattleField *field) const override;

public:
	virtual ~EffectsApplicatorAbility();
};