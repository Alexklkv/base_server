#include "HealAllEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

#include "types.h"

HealAllEffect::HealAllEffect(uint32_t id, ability::Type type, CardMask mask, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator), mask(mask)
{}

HealAllEffect::~HealAllEffect()
{
	delete this->calculator;
}

bool HealAllEffect::on_self_round_start(RoundContext &ctx) const
{
	auto summoner = ctx.owner->get_summoner();
	auto targets = summoner->get_deck()->get_cards(ActiveDeck::CardState::ON_FIELD);

	BattleAction::targets_t log;

	bool result = false;
	for (auto &target : targets)
	{
		if (!this->mask.compare_card(target))
			continue;

		uint16_t heal = this->calculator->get(target->get_max_health());
		heal = ctx.field->heal(ctx.owner, std::make_shared<Combatant>(target, summoner), heal);
		if (heal == 0)
			continue;

		log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::HEAL, (uint32_t)heal));

		result = true;
	}

	ctx.field->write_effect(this, ctx.owner, std::forward<BattleAction::targets_t>(log));

	return result;
}

bool HealAllEffect::on_before_application(StatsContext &) const
{
	return false;
}