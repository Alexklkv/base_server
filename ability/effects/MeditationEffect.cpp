#include "MeditationEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"

#include "battle/RoundActionsLog.h"

MeditationEffect::MeditationEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_HEALTH, 0, policy)
{}

bool MeditationEffect::on_other_round_end(RoundContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto target = combatant->get_card();
	if (target->made_attack)
		return false;

	logger()->debug("Card %" PRIu32 " (player %" PRIu32 ") healed by meditation (made attack = %d)" , target->get_id(), ctx.owner->object_id().summoner_id, target->made_attack);

	uint32_t heal = target->get_injuires();
	ctx.field->heal(combatant, combatant, heal);
	ctx.field->write_effect(this, combatant, {{combatant->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	return true;
}