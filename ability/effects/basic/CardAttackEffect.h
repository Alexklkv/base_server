#pragma once

#include "BattleEffect.h"

class CardAttackEffect : public virtual BattleEffect
{
protected:
	virtual bool on_attacker_before(CardAttackContext &ctx) const;
	virtual bool on_attacker_after(CardAttackContext &ctx) const;
	virtual bool on_target_before(CardAttackContext &ctx) const;
	virtual bool on_target_after(CardAttackContext &ctx) const;

public:
	virtual bool attacker_before(CardAttackContext &ctx) const override;
	virtual bool attacker_after(CardAttackContext &ctx) const override;
	virtual bool target_before(CardAttackContext &ctx) const override;
	virtual bool target_after(CardAttackContext &ctx) const override;
};