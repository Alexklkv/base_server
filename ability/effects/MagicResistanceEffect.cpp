#include "MagicResistanceEffect.h"

#include "BattleAction.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Sharps.h"

#include "battle/RoundActionsLog.h"

#include "params.h"

MagicResistanceEffect::MagicResistanceEffect(uint32_t id, ability::Type type, uint8_t percent, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::SHIELD, 0, policy), percent(percent)
{}

bool MagicResistanceEffect::on_before_application(StatsContext &ctx) const
{
	if (!ctx.owner->is_card())
		return false;

	auto card = ctx.owner->get_card();
	uint8_t extra = Sharps::get_sharp_times(this->get_ability(), card);
	int32_t value = std::min(this->percent * extra, 100);

	bool changed = card->change_extra(BaseCard::ExtraType::MAGIC_RESISTANT, this->get_id(), value);
	if (changed)
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});

	return changed;
}

bool MagicResistanceEffect::on_after_removal(StatsContext &ctx) const
{
	if (!ctx.owner->is_card())
		return false;

	auto card = ctx.owner->get_card();
	card->revert_extra(BaseCard::ExtraType::MAGIC_RESISTANT, this->get_id());

	ctx.log->effect_remove(ctx.owner.get(), this->get_ability(), this->get_effect());

	return true;
}