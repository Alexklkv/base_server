#include "TargetFractionDamageEffect.h"

#include "CardHandler.h"

TargetFractionDamageEffect::TargetFractionDamageEffect(uint32_t id, ability::Type type, CardMask mask, const Calculator *calculator, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::MODIFY_ATTACK, 0, policy_factory), calculator(calculator), mask(mask)
{}

TargetFractionDamageEffect::~TargetFractionDamageEffect()
{
	delete this->calculator;
}

bool TargetFractionDamageEffect::on_attacker_before(CardAttackContext &ctx) const
{
	if (!ctx.target->is_card() || !this->mask.compare_card(ctx.target->get_card()))
		return false;

	auto card = ctx.target->get_card();
	ctx.extra_damage += this->calculator->get(card->get_damage());

	return true;
}