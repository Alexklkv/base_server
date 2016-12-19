#include "CardPlacementEffect.h"

#include "Enum.h"
#include "Log.h"

#include "battle/ActiveEffects.h"

CardPlacementEffect::~CardPlacementEffect()
{
}

bool CardPlacementEffect::on_after_placement(CardAddContext&) const
{
	return false;
}

bool CardPlacementEffect::on_before_placement(CardAddContext&) const
{
	return false;
}

bool CardPlacementEffect::after_placement(CardAddContext &ctx) const
{
	if (!this->on_after_placement(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p after placement", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool CardPlacementEffect::before_placement(CardAddContext &ctx) const
{
	if (!this->on_before_placement(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p before placement", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}