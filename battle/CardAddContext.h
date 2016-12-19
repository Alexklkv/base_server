#pragma once

#include "CardActionContext.h"
#include "Combatant.h"

#include <list>

class BattleField;

class CardAddContext : public CardActionContext
{
public:
	combatant_ptr_t card;
	uint8_t slot;
	bool by_player;

	Summoner *const actor;

	CardAddContext(Summoner *actor, BattleField *field, const combatant_ptr_t &card, uint8_t slot, bool by_player, BattleAction::targets_t &targets);
};