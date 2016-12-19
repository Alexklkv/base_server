#pragma once

#include "basic/PositiveEffect.h"
#include "basic/StatsEffect.h"

class MagicResistanceEffect final : public StatsEffect, public PositiveEffect
{
private:
	uint8_t percent;

protected:
	bool on_before_application(StatsContext &ctx) const override;
	bool on_after_removal(StatsContext &ctx) const override;

public:
	MagicResistanceEffect(uint32_t id, ability::Type type, uint8_t percent, const policy_factory_t &policy);
};