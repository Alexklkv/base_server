#include "PiercingStrikeEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

#include "battle/Combatant.h"

#include <algorithm>

PiercingStrikeEffect::PiercingStrikeEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory), start_target_health(0)
{}

combatant_ptr_t PiercingStrikeEffect::get_target(combatant_ptr_t old_target) const
{
	auto summoner = old_target->get_summoner();
	auto target_card = summoner->get_deck()->get_back_card(old_target->get_card()->get_slot());

	return std::make_shared<Combatant>(target_card, summoner);
}

bool PiercingStrikeEffect::on_attacker_before(CardAttackContext &ctx) const
{
	this->start_target_health = ctx.target->get_health();
	return true;
}

bool PiercingStrikeEffect::on_attacker_after(CardAttackContext &ctx) const
{
	if (!ctx.target->is_card() || !ctx.target->is_dead())
		return false;

	auto target = this->get_target(ctx.target);
	uint32_t damage_rest = unsigned_substract(ctx.get_total_damage(), this->start_target_health);

	ctx.field->damage(ctx.attacker, target, damage_rest);
	ctx.field->write_effect(this, ctx.attacker, {{target->object_id(), DataPacker().pack(ability::Action::ATTACK, damage_rest)}});

	return true;
}