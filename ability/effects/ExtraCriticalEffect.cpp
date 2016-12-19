#include "ExtraCriticalEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "Log.h"

#include "battle/RoundActionsLog.h"

ExtraCriticalEffect::ExtraCriticalEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, policy), calculator(calculator)
{}

ExtraCriticalEffect::~ExtraCriticalEffect()
{
	delete this->calculator;
}

bool ExtraCriticalEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();

	int32_t value = this->calculator->get(card->get_critical());
	card->change_extra(BaseCard::ExtraType::CRITICAL, this->get_id(), value);
	ctx.targets_log.push_back({combatant.get(), DataPacker().pack(ability::Action::ADD_EFFECT, ability::Modifier::MODIFY_CRITICAL, value, ability::Duration::INFINITE)});

	return true;
}

bool ExtraCriticalEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();
	card->revert_extra(BaseCard::ExtraType::CRITICAL, this->get_id());

	ctx.log->effect_remove(combatant.get(), this->get_ability(), ability::Modifier::MODIFY_CRITICAL);

	return true;
}