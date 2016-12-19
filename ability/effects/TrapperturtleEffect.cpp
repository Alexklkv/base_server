#include "TrapperturtleEffect.h"

#include "BattleField.h"
#include "CardHandler.h"

#include "battle/RoundActionsLog.h"

TrapperturtleEffect::TrapperturtleEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::CAN_RESPOND_FLYING, 0, policy)
{}