#pragma once

#include "ComboManager.h"

class ActiveCombos;
class BattleField;
class ComboParams;

struct ComboID;

class EnabledComboManager : public ComboManager
{
	BattleField *const field;
	const ComboParams *const params;

	void remove_combo(RoundActionsLog *log, const cards_set_t &active_cards, Summoner *summoner, ability::Type type);

public:
	EnabledComboManager(BattleField *owner, const ComboParams *combos);

	virtual void apply(RoundActionsLog *log, const combatant_ptr_t &moved) override;
	virtual void reapply(RoundActionsLog *log, const removed_t &removed) override;
	virtual void clear(RoundActionsLog *log, const combatant_ptr_t &moved) override;
	virtual removed_t clear_removed(RoundActionsLog* log, const combatant_ptr_t &removed) override;
};