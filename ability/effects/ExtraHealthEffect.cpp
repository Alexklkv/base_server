#include "ExtraHealthEffect.h"

#include "BattleAction.h"
#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "LegendsServer.h"
#include "Sharps.h"

#include "ability/spells/BattleSpellsParams.h"
#include "battle/RoundActionsLog.h"
#include "retention/RetentionPolicy.h"

#include "params.h"

ExtraHealthEffect::ExtraHealthEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_HEALTH, 0, policy), calculator(calculator)
{}

ExtraHealthEffect::~ExtraHealthEffect()
{
	delete this->calculator;
}

bool ExtraHealthEffect::on_before_application(StatsContext &ctx) const
{
	uint8_t extra = (ctx.owner->is_card()) ? Sharps::get_sharp_times(this->get_ability(), ctx.owner->get_card()) : 1;
	int32_t value = this->calculator->get(ctx.owner->get_base_health()) * extra;

	bool changed = ctx.field->change_health(ctx.owner, this->get_id(), value);
	if (changed)
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});

	return changed;
}

bool ExtraHealthEffect::on_after_removal(StatsContext &ctx) const
{
	if (!ctx.owner->is_card())
		return false;

	ctx.field->revert_health(ctx.owner, this->get_id());
	ctx.log->effect_remove(ctx.owner.get(), this->get_ability(), this->get_effect());

	return true;
}