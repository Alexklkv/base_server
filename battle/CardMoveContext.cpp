#include "CardMoveContext.h"

#include <list>

CardMoveContext::CardMoveContext(BattleField *field, const combatant_ptr_t &card, uint8_t to_slot, bool by_player, BattleAction::targets_t &targets):
	CardActionContext(field, targets)
{
	this->moves.push_back({card, to_slot, by_player});
}