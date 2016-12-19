#pragma once

#include "basic/PositiveEffect.h"
#include "basic/StatsEffect.h"

#include "misc.h"

class EagernessEffect : public StatsEffect, public PositiveEffect
{
protected:
	bool on_before_application(StatsContext &ctx) const override;

public:
	EagernessEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};