#pragma once

#include "CardActionContext.h"
#include "Combatant.h"

class BattleField;

class CardMoveContext : public CardActionContext
{
public:
	struct Entry
	{
		combatant_ptr_t card;
		uint8_t target_slot;
		bool by_player;
	};

	std::list<Entry> moves;

public:
	CardMoveContext(BattleField *field, const combatant_ptr_t &card, uint8_t to_slot, bool by_player, BattleAction::targets_t &targets);
};