#include "ChainReactionEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/Combatant.h"

ChainReactionEffect::ChainReactionEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory)
{}

bool ChainReactionEffect::on_attacker_after(CardAttackContext &ctx) const
{
	if (!ctx.target->is_card())
		return false;

	auto opponent = ctx.target->get_summoner();
	auto deck = opponent->get_deck();
	auto card = deck->get_row_neighbour(ctx.target->get_card());

	if (!card)
		return false;

	auto target = std::make_shared<Combatant>(card, opponent);

	ctx.field->damage(ctx.attacker, target, ctx.get_total_damage());
	ctx.field->write_effect(this, ctx.attacker, {{target->object_id(), DataPacker().pack(ability::Action::ATTACK, ctx.get_total_damage())}});

	return true;
}