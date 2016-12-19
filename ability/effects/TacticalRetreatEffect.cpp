#include "TacticalRetreatEffect.h"

#include "battle/RoundActionsLog.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Summoner.h"

TacticalRetreatEffect::TacticalRetreatEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy)
{}

bool TacticalRetreatEffect::on_target_before(CardAttackContext& ctx) const
{
	auto combatant = ctx.target;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();
	if (card->was_attacked)
		return false;

	uint8_t slot = combatant->get_summoner()->get_deck()->get_neighbour_slot(card);
	if (slot == ActiveDeck::MAX_SLOT)
		return false;

	ctx.forbid();

	ctx.field->card_move(combatant, slot, false);
	ctx.log->card_moved(combatant.get(), slot);

	return true;
}