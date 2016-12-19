#include "SacrificeEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

SacrificeEffect::SacrificeEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory), calculator(calculator)
{}

SacrificeEffect::~SacrificeEffect()
{
	delete this->calculator;
}

bool SacrificeEffect::on_after_removal(StatsContext &ctx) const
{
	auto card = ctx.owner;
	if (!card->is_dead())
		return false;

	auto target_summoner = std::make_shared<Combatant>(card->get_summoner());
	uint32_t heal = this->calculator->get(card->get_summoner()->get_health());

	heal = ctx.field->heal(card, target_summoner, heal);
	ctx.field->write_effect(this, card, {{target_summoner->object_id(), DataPacker().pack(ability::Action::HEAL, heal)}});

	return true;
}