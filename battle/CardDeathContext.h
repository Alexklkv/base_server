#pragma once

#include "CardActionContext.h"
#include "Combatant.h"

class CardDeathContext : public CardActionContext
{
public:
	combatant_ptr_t killer;
	combatant_ptr_t dead;

	CardDeathContext(BattleField *field, const combatant_ptr_t &killer, const combatant_ptr_t &dead, BattleAction::targets_t &targets);
};