#include "SorcererEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

#include "types.h"

SorcererEffect::SorcererEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

SorcererEffect::~SorcererEffect()
{
	delete this->calculator;
}

bool SorcererEffect::on_self_round_start(RoundContext &ctx) const
{
	auto opponent = ctx.field->get_opponent(ctx.owner->get_summoner());
	auto target = opponent->get_deck()->get_random_card(ActiveDeck::CardState::ON_FIELD);
	if (target == nullptr)
		return false;

	uint16_t damage = this->calculator->get(target->get_health());
	ctx.field->damage(ctx.owner, std::make_shared<Combatant>(target, opponent), damage);
	ctx.field->write_effect(this, ctx.owner, {{target->object_id(), DataPacker().pack(ability::Action::ATTACK, (uint32_t)damage)}});

	return true;
}

bool SorcererEffect::on_before_application(StatsContext &) const
{
	return false;
}