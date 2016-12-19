#include "DaturaEffect.h"

#include "BattleField.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

#include "ability/spells/Spell.h"
#include "battle/Combatant.h"
#include "battle/RoundActionsLog.h"

DaturaEffect::DaturaEffect(uint32_t id, ability::Type type, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::DATURA, 0, policy_factory)
{}

bool DaturaEffect::on_before_caster(CardSpellContext &ctx) const
{
	if (ctx.targets.empty())
	{
		logger()->warning("Datura effect on empty spell");
		return false;
	}

	Summoner *summoner = ctx.field->random_summoner();
	combatant_ptr_t summoner_cmb = std::make_shared<Combatant>(ctx.caster);
	CardHandler *random_card = summoner->get_deck()->get_random_card(ActiveDeck::ON_FIELD);
	combatant_ptr_t new_target = std::make_shared<Combatant>(random_card, summoner);
	ctx.targets = ctx.spell->targets(summoner_cmb, new_target, ctx.field);
	ctx.log->effect(ctx.caster, this);

	return true;
}