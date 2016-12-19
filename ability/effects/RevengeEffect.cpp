#include "RevengeEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Summoner.h"

#include "battle/RoundActionsLog.h"

RevengeEffect::RevengeEffect(uint32_t id, ability::Type type, Calculator *calculator, const policy_factory_t &policy_factory):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy_factory), calculator(calculator)
{}

RevengeEffect::~RevengeEffect()
{
	delete this->calculator;
}

bool RevengeEffect::on_after_removal(StatsContext &ctx) const
{
	auto card = ctx.owner;
	if (!card->is_dead())
		return false;

	auto target_card = ctx.caster;
	if (ctx.caster == nullptr)
		return false;

	uint32_t value = this->calculator->get(target_card->get_damage());

	bool changed = target_card->change_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id(), value);
	if (changed)
		ctx.targets_log.push_back({target_card->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});

	return changed;
}