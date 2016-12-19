#pragma once

#include "BattleAction.h"			// BattleAction::targets_t
#include "Combatant.h"				// combatant_ptr_t
#include "NoCopy.h"

#include <vector>

class Ability;
class BattleField;

class PassiveAbilities : private NoCopy
{
public:
	typedef std::vector<const Ability*> passives_t;

private:
	passives_t passives;

public:
	void assign(passives_t &&passives);
	void insert(passives_t &&passives);
	void apply(BattleAction::targets_t &log, combatant_ptr_t &owner, BattleField *field) const;

#ifdef DEBUG
	void debug_state(std::stringstream &debug_data) const;
#endif
};