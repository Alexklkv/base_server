#pragma once

#include "Combo.h"

#include <list>

class BattleEffect;
class RoundActionsLog;

class EffectApplyingCombo : public virtual Combo
{
private:
	typedef std::list<const BattleEffect*> effects_t;

	const effects_t effects;

protected:
	virtual bool do_apply(RoundActionsLog *log, ComboID combo, const ComboTargeting::targets_t &targets, BattleField *field) const override;

public:
	EffectApplyingCombo(std::initializer_list<const BattleEffect*> effects);
	virtual ~EffectApplyingCombo();
};