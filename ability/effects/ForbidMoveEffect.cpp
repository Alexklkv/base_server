#include "ForbidMoveEffect.h"

#include "BattleField.h"
#include "DataPacker.h"

ForbidMoveEffect::ForbidMoveEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::BLOCK_MOVE, 0, policy_factory)
{}

bool ForbidMoveEffect::on_before_move(CardMoveContext &ctx) const
{
	if (ctx.moves.empty())
		return false;

	ctx.moves.clear();
	return true;
}