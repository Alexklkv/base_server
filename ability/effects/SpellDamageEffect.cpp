#include "SpellDamageEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "LegendsServer.h"
#include "Summoner.h"

#include "ability/spells/BattleSpellsParams.h"
#include "battle/RoundActionsLog.h"

#include "types.h"

SpellDamageEffect::SpellDamageEffect(uint32_t id, ability::Type type, CardMask mask, Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator), mask(mask)
{}

SpellDamageEffect::~SpellDamageEffect()
{
	delete this->calculator;
}

bool SpellDamageEffect::on_before_application(StatsContext &ctx) const
{
	int32_t value = this->calculator->get(ctx.owner->get_max_health());
	value += ctx.caster->get_spell_strength_bonus(value);

	uint16_t changed = ctx.field->damage(ctx.caster, ctx.owner, value);
	ctx.targets_log.emplace_back(ctx.owner->object_id(), DataPacker().pack(ability::Action::ATTACK, (int16_t)changed));
	auto spell = battle_spells()->get(this->get_ability());
	ctx.log->spell(ctx.caster.get(), spell, std::move(ctx.targets_log));
	return true;
}