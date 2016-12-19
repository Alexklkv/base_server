#pragma once

#include "BattleEffect.h"

class RoundEffect : public virtual BattleEffect
{
protected:
	virtual bool on_self_round_start(RoundContext &ctx) const;
	virtual bool on_self_round_end(RoundContext &ctx) const;
	virtual bool on_other_round_start(RoundContext &ctx) const;
	virtual bool on_other_round_end(RoundContext &ctx) const;

public:
	virtual bool self_round_start(RoundContext &ctx) const override;
	virtual bool self_round_end(RoundContext &ctx) const override;
	virtual bool other_round_start(RoundContext &ctx) const override;
	virtual bool other_round_end(RoundContext &ctx) const override;
};