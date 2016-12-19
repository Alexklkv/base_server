#include "ExtraDodgeEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

ExtraDodgeEffect::ExtraDodgeEffect(uint32_t id, ability::Type type, const Calculator *c, const policy_factory_t &p):
	BattleEffect(id, type, ability::Modifier::MODIFY_DODGE, 0, p), calculator(c)
{}

ExtraDodgeEffect::~ExtraDodgeEffect()
{
	delete this->calculator;
}

bool ExtraDodgeEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();

	float value = this->calculator->get(card->get_dodge());
	bool changed = card->change_extra(BaseCard::ExtraType::DOODGE, this->get_id(), value * 100);
	if (changed)
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});

	return changed;
}

bool ExtraDodgeEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();
	card->revert_extra(BaseCard::ExtraType::DOODGE, this->get_id());

	ctx.log->effect_remove(combatant.get(), this->get_ability(), this->get_effect());

	return true;
}