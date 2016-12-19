#include "CardDeathContext.h"

CardDeathContext::CardDeathContext(BattleField *field, const combatant_ptr_t &killer, const combatant_ptr_t &dead, BattleAction::targets_t &targets):
	CardActionContext(field, targets), killer(killer), dead(dead)
{}