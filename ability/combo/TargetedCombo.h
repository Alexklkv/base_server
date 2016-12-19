#pragma once

#include "Combo.h"

class TargetedCombo : public virtual Combo
{
public:
	using picker_t = ComboTargeting::picker_t;
	using targets_t = ComboTargeting::targets_t;

private:
	picker_t picker;

protected:
	explicit TargetedCombo(const picker_t &picker);

public:
	virtual targets_t targets(BattleField *field, const combatant_ptr_t &moved) const override;
};