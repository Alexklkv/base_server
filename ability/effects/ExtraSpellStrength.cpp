#include "ExtraSpellStrength.h"

#include "BattleAction.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"
#include "battle/Target.h"

ExtraSpellStrength::ExtraSpellStrength(uint32_t id, ability::Type type, uint8_t percent, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_SPELL_INJUIRE, 0, policy), percent(percent)
{}

bool ExtraSpellStrength::on_before_application(StatsContext &ctx) const
{
	if (ctx.owner->is_card())
		return false;

	auto summoner = ctx.owner->get_summoner();
	bool changed = summoner->change_extra(BaseCard::SPELL_STRENGTH, this->get_id(), this->percent);

	if (changed)
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)this->percent, ability::Duration::INFINITE)});

	return changed;
}

bool ExtraSpellStrength::on_after_removal(StatsContext &ctx) const
{
	if (ctx.owner->is_card())
		return false;

	auto summoner = ctx.owner->get_summoner();
	bool changed = (summoner->revert_extra(BaseCard::SPELL_STRENGTH, this->get_id()) > 0);

	if (changed)
		ctx.log->effect_remove(ctx.owner.get(), this->get_ability(), this->get_effect());

	return changed;
}