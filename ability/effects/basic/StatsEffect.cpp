#include "StatsEffect.h"

#include "Enum.h"
#include "Log.h"

#include "battle/ActiveEffects.h"

bool StatsEffect::on_before_application(StatsContext &) const
{
	return false;
}

bool StatsEffect::on_after_removal(StatsContext &) const
{
	return false;
}

bool StatsEffect::before_application(StatsContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied before application: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!BattleEffect::before_application(ctx))
		return false;

	if (!this->on_before_application(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p before application", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool StatsEffect::after_removal(StatsContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied before application: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_after_removal(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p after application", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}