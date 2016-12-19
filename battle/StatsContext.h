#pragma once

#include "CardActionContext.h"
#include "Combatant.h"

class BattleField;

class StatsContext : public CardActionContext
{
public:
	combatant_ptr_t owner;
	combatant_ptr_t caster;

	bool blocked = false;
	bool forbidden = false;

	StatsContext(const combatant_ptr_t &owner, BattleField *field, BattleAction::targets_t &targets, const combatant_ptr_t &caster = nullptr);

	bool is_possible() const;
};