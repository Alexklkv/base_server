#pragma once

#include "CardActionContext.h"
#include "Combatant.h"

class BattleField;

class RoundContext : public CardActionContext
{
public:
	const combatant_ptr_t owner;

	bool forbidden = false;

	RoundContext(const combatant_ptr_t &owner, BattleField *field, BattleAction::targets_t &targets);

	bool is_possible() const;
};