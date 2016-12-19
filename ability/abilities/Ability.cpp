#include "Ability.h"

#include "BattleField.h"
#include "Exception.h"

Ability::Ability():
	type(ability::NO_ABILITY)
{
	throw Exception("This constructor is for virtual inheritance compile-time check only");
}

Ability::Ability(ability::Type type):
	type(type)
{}

void Ability::apply(BattleAction::targets_t &log, combatant_ptr_t &caster, BattleField *field) const
{
	auto targets = this->targets(caster, field);

	for (combatant_ptr_t &target : targets)
		this->do_apply(log, caster, target, field);
}

ability::Type Ability::get_ability() const
{
	return this->type;
}