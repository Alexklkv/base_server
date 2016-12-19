#include "MirrorShieldEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

MirrorShieldEffect::MirrorShieldEffect(uint32_t id, ability::Type type, CardMask mask, const Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), mask(mask), calculator(calculator)
{}

MirrorShieldEffect::~MirrorShieldEffect()
{
	delete this->calculator;
}

bool MirrorShieldEffect::on_target_after(CardAttackContext &ctx) const
{
	if (!ctx.attacker->is_card() || !this->mask.compare_card(ctx.attacker->get_card()))
		return false;

	uint16_t damage = this->calculator->get(ctx.get_total_damage());

	ctx.field->damage(ctx.target, ctx.attacker, damage);
	ctx.field->write_effect(this, ctx.target, {{ctx.attacker->object_id(), DataPacker().pack(ability::Action::ATTACK, damage)}});

	return true;
}