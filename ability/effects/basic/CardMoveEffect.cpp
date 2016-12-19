#include "CardMoveEffect.h"

#include "Enum.h"
#include "Log.h"

#include "battle/ActiveEffects.h"

bool CardMoveEffect::on_after_move(CardMoveContext&) const
{
	return false;
}

bool CardMoveEffect::on_before_move(CardMoveContext&) const
{
	return false;
}

bool CardMoveEffect::after_move(CardMoveContext &ctx) const
{
	if (!this->on_after_move(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p after move", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool CardMoveEffect::before_move(CardMoveContext &ctx) const
{
	if (!this->on_before_move(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p before move", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}