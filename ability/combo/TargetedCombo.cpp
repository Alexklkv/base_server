#include "TargetedCombo.h"

TargetedCombo::TargetedCombo(const picker_t &picker):
	picker(picker)
{}

TargetedCombo::targets_t TargetedCombo::targets(BattleField *field, const combatant_ptr_t &moved) const
{
	return this->picker(field, moved);
}