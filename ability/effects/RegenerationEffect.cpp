#include "RegenerationEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

RegenerationEffect::RegenerationEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

RegenerationEffect::~RegenerationEffect()
{
	delete this->calculator;
}

bool RegenerationEffect::on_self_round_start(RoundContext &ctx) const
{
	auto card = ctx.owner->get_card();

	uint16_t heal = this->calculator->get(card->get_base_health());
	heal = ctx.field->heal(ctx.owner, ctx.owner, heal);
	if (heal)
		ctx.field->write_effect(this, ctx.owner, {{card->object_id(), DataPacker().pack(ability::Action::HEAL, (uint32_t)heal)}});

	return true;
}