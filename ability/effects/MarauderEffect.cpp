#include "MarauderEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "basic/StatsEffect.h"
#include "battle/RoundActionsLog.h"

MarauderEffect::MarauderEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_ATTACK, 0, policy), calculator(calculator)
{}

MarauderEffect::~MarauderEffect()
{
	delete this->calculator;
}

bool MarauderEffect::on_attacker_after(CardAttackContext &ctx) const
{
	if (!ctx.target->is_dead())
		return false;

	auto card = ctx.attacker->get_card();

	int16_t value = this->calculator->get(card->get_base_damage());
	int16_t old_value = card->revert_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id());
	if (!card->change_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id(), value + old_value))
		return false;

	ctx.field->write_effect(this, ctx.attacker, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(value), ability::Duration::INFINITE)}});
	return true;
}