#include "DiscardExtraEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"

#include "battle/RoundActionsLog.h"

DiscardExtraEffect::DiscardExtraEffect(uint32_t id, ability::Type type, const policy_factory_t &p):
	BattleEffect(id, type, ability::Modifier::BLOCK_MODIFIER_EFFECT, 0, p)
{}

bool DiscardExtraEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)0, ability::Duration::INFINITE)});
	return true;
}

bool DiscardExtraEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	ctx.log->effect_remove(combatant.get(), this->get_ability(), this->get_effect());
	return true;
}