#pragma once

#include "BattleEffect.h"

class StatsEffect : public virtual BattleEffect
{
protected:
	virtual bool on_before_application(StatsContext &ctx) const;
	virtual bool on_after_removal(StatsContext &ctx) const;

public:
	virtual bool before_application(StatsContext &ctx) const override;
	virtual bool after_removal(StatsContext &ctx) const override;
};