#include "StatsContext.h"

#include "BattleAction.h"

StatsContext::StatsContext(const combatant_ptr_t &owner, BattleField *field, BattleAction::targets_t &targets, const combatant_ptr_t &caster):
	CardActionContext(field, targets), owner(owner), caster(caster)
{}

bool StatsContext::is_possible() const
{
	return (!this->blocked && !this->forbidden);
}