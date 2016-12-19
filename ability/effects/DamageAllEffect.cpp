#include "DamageAllEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

#include "types.h"

DamageAllEffect::DamageAllEffect(uint32_t id, ability::Type type, CardMask mask, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator), mask(mask)
{}

DamageAllEffect::~DamageAllEffect()
{
	delete this->calculator;
}

bool DamageAllEffect::on_other_round_start(RoundContext &ctx) const
{
	auto opponent = ctx.field->get_opponent(ctx.owner->get_summoner());
	auto targets = opponent->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);
	BattleAction::targets_t log;

	bool result = false;
	for (auto &target : targets)
	{
		if (!this->mask.compare_card(target))
			continue;

		uint16_t damage = this->calculator->get(target->get_health());
		ctx.field->damage(ctx.owner, std::make_shared<Combatant>(target, opponent), damage);
		log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::ATTACK, (uint32_t)damage));

		result = true;
	}

	ctx.field->write_effect(this, ctx.owner, std::forward<BattleAction::targets_t>(log));

	return result;
}

bool DamageAllEffect::on_before_application(StatsContext &) const
{
	return false;
}