#include "DrainingEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Exception.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

DrainingEffect::DrainingEffect(uint32_t id, ability::Type type, int8_t mana_change, const policy_factory_t &factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, factory), mana_change(mana_change)
{}

bool DrainingEffect::on_self_round_start(RoundContext &ctx) const
{
	if (!ctx.owner->is_summoner())
		throw Exception("Non-summoner target supplied to draining effect");

	auto target = ctx.owner->get_summoner();
	target->change_extra_mana(this->get_id(), this->mana_change);

	ctx.log->effect(ctx.owner.get(), ctx.owner.get(), this, DataPacker().pack(ability::Action::CHANGE_MANA, (int16_t)this->mana_change));

	return true;
}