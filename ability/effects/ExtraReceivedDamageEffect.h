#pragma once

#include "basic/NegativeEffect.h"
#include "basic/StatsEffect.h"

#include "misc.h"

class ExtraReceivedDamageEffect : public StatsEffect, public NegativeEffect
{
private:
	BaseCard::Range range;
	BaseCard::Fraction fraction;
	mutable BaseCard::ExtraType applied_type;
	uint8_t value;

	static BaseCard::ExtraType convert_range(BaseCard::Range range);
	static BaseCard::ExtraType convert_fraction(BaseCard::Fraction fraction);

protected:
	bool on_before_application(StatsContext &ctx) const override;
	bool on_after_removal(StatsContext &ctx) const override;

public:
	ExtraReceivedDamageEffect(uint32_t id, ability::Type type, BaseCard::Range range, BaseCard::Fraction fraction, int8_t value, const policy_factory_t &policy_factory);
};