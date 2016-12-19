#include "ShieldEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

ShieldEffect::ShieldEffect(uint32_t id, ability::Type type, const policy_factory_t &p):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, p)
{}

bool ShieldEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();

	card->add_shield(this->get_id(), 0);
	ctx.targets_log.push_back({combatant.get(), DataPacker().pack(ability::Action::ADD_EFFECT, ability::Modifier::SHIELD, (uint16_t)0, ability::Duration::TEMPORARY)});

	return true;
}

bool ShieldEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	ctx.log->effect_remove(combatant.get(), this->get_ability(), ability::Modifier::SHIELD);

	return true;
}