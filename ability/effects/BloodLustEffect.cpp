#include "BloodLustEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

BloodLustEffect::BloodLustEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

BloodLustEffect::~BloodLustEffect()
{
	delete this->calculator;
}

bool BloodLustEffect::on_self_round_end(RoundContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto target = combatant->get_card();
	if (target->made_attack)
		return false;

	uint32_t damage = this->calculator->get(target->get_health());
	ctx.field->damage(combatant, combatant, damage);
	ctx.field->write_effect(this, combatant, {{combatant->object_id(), DataPacker().pack(ability::Action::ATTACK, (uint32_t)damage)}});

	return true;
}