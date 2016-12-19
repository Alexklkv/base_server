#pragma once

#include "basic/NegativeEffect.h"
#include "basic/StatsEffect.h"

#include "misc.h"

class DiscardExtraEffect final : public StatsEffect, public NegativeEffect
{
private:
	bool on_before_application(StatsContext &ctx) const override;
	bool on_after_removal(StatsContext &ctx) const override;

public:
	DiscardExtraEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};