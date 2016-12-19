#pragma once

#include "BattleEffect.h"

class SpellEffect : public virtual BattleEffect
{
protected:
	virtual bool on_before_caster(CardSpellContext &ctx) const;
	virtual bool on_after_caster(CardSpellContext &ctx) const;
	virtual bool on_before_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const;
	virtual bool on_after_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const;

public:
	virtual bool before_caster(CardSpellContext &ctx) const override;
	virtual bool after_caster(CardSpellContext &ctx) const override;
	virtual bool before_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const override;
	virtual bool after_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const override;
};