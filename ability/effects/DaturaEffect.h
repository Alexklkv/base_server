#pragma once

#include "ability/effects/basic/NegativeEffect.h"
#include "ability/effects/basic/SpellEffect.h"

class DaturaEffect : public SpellEffect, public NegativeEffect
{
protected:
	virtual bool on_before_caster(CardSpellContext &ctx) const override;

public:
	DaturaEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};