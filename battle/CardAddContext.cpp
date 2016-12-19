#include "CardAddContext.h"

CardAddContext::CardAddContext(Summoner *actor, BattleField *field, const combatant_ptr_t &card, uint8_t slot, bool by_player, BattleAction::targets_t &targets):
	CardActionContext(field, targets), card(card), slot(slot), by_player(by_player), actor(actor)
{}