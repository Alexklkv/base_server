#pragma once

#include "basic/PositiveEffect.h"
#include "basic/StatsEffect.h"

class IllusionEffect : public StatsEffect, public PositiveEffect
{
	typedef std::pair<uint16_t, uint16_t> params_t;

private:
	params_t get_middle_params(const cards_set_t &&cards) const;

protected:
	virtual bool on_before_application(StatsContext &ctx) const override;
	virtual bool on_after_removal(StatsContext &ctx) const override;

public:
	IllusionEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory);
};
