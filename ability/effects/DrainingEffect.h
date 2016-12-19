#pragma once

#include "basic/NegativeEffect.h"
#include "basic/RoundEffect.h"

class DrainingEffect : public NegativeEffect, public RoundEffect
{
private:
	const int8_t mana_change;

protected:
	virtual bool on_self_round_start(RoundContext& ctx) const override;

public:
	DrainingEffect(uint32_t id, ability::Type type, int8_t mana_change, const policy_factory_t &factory);
};