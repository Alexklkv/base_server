#include "PassiveAbilities.h"

#include "BattleField.h"

#include "ability/abilities/Ability.h"

void PassiveAbilities::assign(passives_t &&new_passives)
{
	this->passives = std::forward<passives_t>(new_passives);
}

void PassiveAbilities::insert(passives_t &&new_passives)
{
	this->passives.insert(this->passives.begin(), new_passives.begin(), new_passives.end());
}

void PassiveAbilities::apply(BattleAction::targets_t &log, combatant_ptr_t &owner, BattleField *field) const
{
	for (const Ability *ability : this->passives)
		ability->apply(log, owner, field);
}

#ifdef DEBUG

void PassiveAbilities::debug_state(std::stringstream &debug_data) const
{
	debug_data << "Passive abilities: ";
	for (auto ability: this->passives) {
		debug_data << static_cast<uint32_t>(ability->get_ability()) << " ";
	}

	debug_data << std::endl;
}

#endif