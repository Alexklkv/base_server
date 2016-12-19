#include "InsanityEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

InsanityEffect::InsanityEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy)
{}

bool InsanityEffect::on_self_round_start(RoundContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();
	auto opponent = ctx.field->get_opponent(combatant->get_summoner());

	auto cards = opponent->get_deck()->get_on_vertical(card->get_slot());
	if (cards.empty())
		return false;

	auto target_combatant = std::make_shared<Combatant>(*cards.begin(), opponent);

	if (!ctx.field->can_attack(combatant, target_combatant, false, false, false, true))
		return false;

	ctx.field->attack_card(combatant, target_combatant, false);

	return true;
}