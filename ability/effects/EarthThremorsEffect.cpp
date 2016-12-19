#include "EarthThremorsEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

EarthThremorsEffect::EarthThremorsEffect(uint32_t id, ability::Type type, CardMask mask, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), mask(mask), calculator(calculator)
{}

EarthThremorsEffect::~EarthThremorsEffect()
{
	delete this->calculator;
}

bool EarthThremorsEffect::on_after_move(CardMoveContext &ctx) const
{
	auto combatant = ctx.moves.front().card;
	if (!combatant->is_card())
		return false;

	auto attacker = combatant->get_card();
	auto opponent = ctx.field->get_opponent(combatant->get_summoner());
	auto targets = opponent->get_deck()->get_on_vertical(attacker->get_slot());

	BattleAction::targets_t targets_log;

	for (auto &target : targets)
	{
		uint16_t damage = this->calculator->get(target->get_health());
		ctx.field->damage(combatant, std::make_shared<Combatant>(target, opponent), damage);

		targets_log.emplace_back(target->object_id(), DataPacker().pack(ability::Action::ATTACK, (uint32_t)damage));
	}

	ctx.field->write_effect(this, combatant, std::move(targets_log));

	return true;
}

bool EarthThremorsEffect::on_before_application(StatsContext &) const
{
	return false;
}