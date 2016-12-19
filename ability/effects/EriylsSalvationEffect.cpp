#include "EriylsSalvationEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

EriylsSalvationEffect::EriylsSalvationEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_HEALTH, 0, policy)
{}

bool EriylsSalvationEffect::on_other_round_end(RoundContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto target = combatant->get_card();
	if (target->was_attacked)
		return false;

	uint32_t heal = target->get_injuires();
	ctx.field->heal(combatant, combatant, heal);
	ctx.field->write_effect(this, combatant, {{combatant->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	return true;
}