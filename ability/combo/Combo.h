#pragma once

#include "ComboID.h"
#include "ComboTargeting.h"

class BattleField;
class RoundActionsLog;

class Combo
{
public:
	typedef std::vector<ability::Type> predecessors_t;

private:
	ability::Type type;
	predecessors_t predecessors;

protected:
	virtual bool do_apply(RoundActionsLog *log, ComboID combo, const ComboTargeting::targets_t &targets, BattleField *field) const = 0;

public:
	Combo();
	Combo(ability::Type type, std::initializer_list<ability::Type> predecessors);
	virtual ~Combo();

	ability::Type get_ability() const;
	const predecessors_t& get_predecessors() const;

	virtual bool apply(RoundActionsLog *log, const ComboTargeting::targets_t &targets, BattleField *field) const;
	virtual ComboTargeting::targets_t targets(BattleField *field, const combatant_ptr_t &moved) const = 0;
};