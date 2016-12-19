#include "DisabledComboManager.h"

DisabledComboManager::DisabledComboManager()
{}

void DisabledComboManager::apply(RoundActionsLog*, const combatant_ptr_t&)
{}

void DisabledComboManager::reapply(RoundActionsLog*, const removed_t&)
{}

void DisabledComboManager::clear(RoundActionsLog*, const combatant_ptr_t&)
{}

DisabledComboManager::removed_t DisabledComboManager::clear_removed(RoundActionsLog*, const combatant_ptr_t&)
{
	return removed_t();
}