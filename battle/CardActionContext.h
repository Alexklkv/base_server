#pragma once

#include "BattleAction.h"

#include "enums.h"

#include <list>

class BattleField;
class RoundActionsLog;

class CardActionContext
{
protected:
	CardActionContext(BattleField *field);
	CardActionContext(BattleField *field, BattleAction::targets_t &targets);

public:
	std::list<ability::Type> affected_by;
	BattleField *const field;
	RoundActionsLog *const log;
	BattleAction::targets_t targets_log;

	void changed_by(ability::Type ability);
};