#include "VampirismEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

VampirismEffect::VampirismEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

VampirismEffect::~VampirismEffect()
{
	delete this->calculator;
}

bool VampirismEffect::on_attacker_after(CardAttackContext &ctx) const
{
	auto combatant = ctx.attacker;
	if (!combatant->is_card())
		return false;

	uint32_t heal = this->calculator->get(ctx.get_total_damage());
	ctx.field->heal(combatant, combatant, heal);
	ctx.field->write_effect(this, combatant, {{combatant->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	return true;
}