#include "CardAttackEffect.h"

#include "Enum.h"
#include "Log.h"

#include "battle/ActiveEffects.h"

bool CardAttackEffect::on_attacker_before(CardAttackContext&) const
{
	return false;
}

bool CardAttackEffect::on_attacker_after(CardAttackContext&) const
{
	return false;
}

bool CardAttackEffect::on_target_before(CardAttackContext&) const
{
	return false;
}

bool CardAttackEffect::on_target_after(CardAttackContext&) const
{
	return false;
}

bool CardAttackEffect::attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied before attacker attack: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_attacker_before(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p before attacker attack", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool CardAttackEffect::attacker_after(CardAttackContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied after attacker attack: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_attacker_after(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p after attacker attack", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool CardAttackEffect::target_before(CardAttackContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied before target attack: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_target_before(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p before target attack", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool CardAttackEffect::target_after(CardAttackContext &ctx) const
{
	if (!ctx.is_possible())
	{
		logger()->debug("Ability %u not applied after target attack: context action is impossible", enum_unwrap(this->get_ability()));
		return false;
	}

	if (!this->on_target_after(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p after target attack", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}