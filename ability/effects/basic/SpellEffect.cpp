#include "SpellEffect.h"

#include "Enum.h"
#include "Log.h"

#include "battle/ActiveEffects.h"

bool SpellEffect::on_after_caster(CardSpellContext&) const
{
	return false;
}

bool SpellEffect::on_before_caster(CardSpellContext&) const
{
	return false;
}

bool SpellEffect::on_after_target(CardSpellContext&, combatant_ptr_t&) const
{
	return false;
}

bool SpellEffect::on_before_target(CardSpellContext&, combatant_ptr_t&) const
{
	return false;
}

bool SpellEffect::after_caster(CardSpellContext &ctx) const
{
	if (!this->on_after_caster(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p caster after spell", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool SpellEffect::before_caster(CardSpellContext &ctx) const
{
	if (!this->on_before_caster(ctx))
		return false;

	logger()->debug("Ability %u applied to battle %p caster before spell", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool SpellEffect::after_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const
{
	if (!this->on_after_target(ctx, current_target))
		return false;

	logger()->debug("Ability %u applied to battle %p target after spell", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}

bool SpellEffect::before_target(CardSpellContext &ctx, combatant_ptr_t &current_target) const
{
	if (!this->on_before_target(ctx, current_target))
		return false;

	logger()->debug("Ability %u applied to battle %p target before spell", enum_unwrap(this->get_ability()), (void*)ctx.field);
	ctx.changed_by(this->get_ability());

	return true;
}