#pragma once

#include "BattleEffect.h"

class CardMoveEffect : public virtual BattleEffect
{
protected:
	virtual bool on_before_move(CardMoveContext &ctx) const;
	virtual bool on_after_move(CardMoveContext &ctx) const;

public:
	virtual bool before_move(CardMoveContext &ctx) const override;
	virtual bool after_move(CardMoveContext &ctx) const override;
};