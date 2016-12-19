#include "RoundEffect.h"

#include "Enum.h"
#include "Log.h"

#include "battle/ActiveEffects.h"

bool RoundEffect::on_self_round_start(RoundContext &) const
{
	return false;
}

bool RoundEffect::on_self_round_end(RoundContext &) const
{
	return false;
}

bool RoundEffect::on_other_round_start(RoundContext &) const
{
	return false;
}

bool RoundEffect::on_other_round_end(RoundContext &) const
{
	return false;
}

bool RoundEffect::self_round_start(RoundContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied on self round start: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_self_round_start(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p on self round start", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool RoundEffect::self_round_end(RoundContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied on self round end: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_self_round_end(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p on self round end", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool RoundEffect::other_round_start(RoundContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied on other round start: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_other_round_start(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p on other round start", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool RoundEffect::other_round_end(RoundContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied on other round end: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_other_round_end(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p on other round end", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}