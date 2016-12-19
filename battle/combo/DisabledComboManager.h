#pragma once

#include "ComboManager.h"

class DisabledComboManager : public ComboManager
{
public:
	DisabledComboManager();

	virtual void apply(RoundActionsLog *log, const combatant_ptr_t &moved) override;
	virtual void reapply(RoundActionsLog* log, const removed_t& removed) override;

	virtual void clear(RoundActionsLog *log, const combatant_ptr_t &moved) override;
	virtual removed_t clear_removed(RoundActionsLog *log, const combatant_ptr_t &removed) override;
};