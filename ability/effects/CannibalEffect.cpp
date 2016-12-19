#include "CannibalEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

CannibalEffect::CannibalEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_HEALTH, 0, policy)
{}

bool CannibalEffect::on_attacker_after(CardAttackContext &ctx) const
{
	if (!ctx.target->is_dead())
		return false;

	auto combatant = ctx.attacker;
	auto card = combatant->get_card();

	uint32_t heal = card->get_max_health();
	heal = ctx.field->heal(combatant, combatant, heal);
	ctx.field->write_effect(this, combatant, {{combatant->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	return true;
}

bool CannibalEffect::on_target_after(CardAttackContext &ctx) const
{
	if (!ctx.attacker->is_dead())
		return false;

	auto combatant = ctx.target;
	auto card = combatant->get_card();

	uint32_t heal = card->get_max_health();
	heal = ctx.field->heal(combatant, combatant, heal);
	ctx.field->write_effect(this, combatant, {{combatant->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	return true;
}