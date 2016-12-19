#include "AttackMoveEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

AttackMoveEffect::AttackMoveEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory)
{}

bool AttackMoveEffect::on_before_application(StatsContext &ctx) const
{
	if (!ctx.owner->is_card() || ctx.owner->get_card()->is_flying())
		return false;

	auto slot = ctx.owner->get_summoner()->get_deck()->get_empty_far_slot();
	if (slot == ActiveDeck::MAX_SLOT)
		return false;

	ctx.field->card_move(ctx.owner, slot, false);
	ctx.log->card_moved(ctx.owner.get(), slot);
	return true;
}