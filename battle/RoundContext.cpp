#include "RoundContext.h"

RoundContext::RoundContext(const combatant_ptr_t &owner, BattleField *field, BattleAction::targets_t &targets):
	CardActionContext(field, targets), owner(owner)
{}

bool RoundContext::is_possible() const
{
	return !this->forbidden;
}