#pragma once

#include "battle/Combatant.h"

#include <list>

class RoundActionsLog;

class ComboManager
{
public:
	struct Removed
	{
		ability::Type type;
		combatant_ptr_t matching;
	};

	typedef std::list<Removed> removed_t;

	virtual ~ComboManager() = default;

	virtual void apply(RoundActionsLog *log, const combatant_ptr_t &moved) = 0;
	virtual void reapply(RoundActionsLog *log, const removed_t &removed) = 0;

	virtual void clear(RoundActionsLog *log, const combatant_ptr_t &moved) = 0;
	virtual removed_t clear_removed(RoundActionsLog *log, const combatant_ptr_t &removed) = 0;
};