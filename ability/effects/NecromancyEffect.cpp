#include "NecromancyEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"
#include "Summoner.h"

#include "types.h"

#include <algorithm>

NecromancyEffect::NecromancyEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

NecromancyEffect::~NecromancyEffect()
{
	delete this->calculator;
}

bool NecromancyEffect::on_target_after(CardAttackContext &ctx) const
{
	if (ctx.is_response)
		return false;

	auto combatant = ctx.target;
	auto card = combatant->get_card();
	if (card == nullptr)
		return false;

	if (card->is_dead())
		return false;

	uint16_t heal = this->calculator->get(ctx.get_total_damage());
	if (heal == 0)
		return false;

	ctx.field->heal(combatant, combatant, heal);
	ctx.field->write_effect(this, combatant, {{card->object_id(), DataPacker().pack(ability::Action::HEAL, (uint32_t)heal)}});

	return true;
}