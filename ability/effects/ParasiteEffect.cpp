#include "ParasiteEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

ParasiteEffect::ParasiteEffect(uint32_t id, ability::Type type, const Calculator *damage, const policy_factory_t &factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, factory), calculator(damage)
{}

ParasiteEffect::~ParasiteEffect()
{
	delete this->calculator;
}

bool ParasiteEffect::on_self_round_start(RoundContext &ctx) const
{
	if (ctx.owner->is_dead())
		return false;

	auto damage = this->calculator->get(ctx.owner->get_card()->get_damage());

	combatant_ptr_t summoner = std::make_shared<Combatant>(ctx.owner->get_summoner());
	ctx.field->damage(ctx.owner, summoner, damage);
	ctx.log->effect(ctx.owner.get(), summoner.get(), this, DataPacker().pack(ability::Action::ATTACK, (uint16_t)damage));

	return true;
}