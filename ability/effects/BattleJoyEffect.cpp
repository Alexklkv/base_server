#include "BattleJoyEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

BattleJoyEffect::BattleJoyEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_HEALTH, 0, policy), calculator(calculator)
{}

BattleJoyEffect::~BattleJoyEffect()
{
	delete this->calculator;
}

bool BattleJoyEffect::on_attacker_after(CardAttackContext &ctx) const
{
	if (!ctx.target->is_dead())
		return false;

	auto card = ctx.attacker->get_card();

	int16_t value = this->calculator->get(card->get_base_health());
	int16_t old_value = card->revert_extra(BaseCard::ExtraType::HEALTH, this->get_id());
	if (!card->change_extra(BaseCard::ExtraType::HEALTH, this->get_id(), value + old_value))
		return false;

	ctx.field->write_effect(this, ctx.attacker, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(value), ability::Duration::INFINITE)}});
	return true;
}

bool BattleJoyEffect::on_before_application(StatsContext &) const
{
	return false;
}