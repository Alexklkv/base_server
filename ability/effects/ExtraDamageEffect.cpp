#include "ExtraDamageEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "LegendsServer.h"
#include "Sharps.h"

#include "ability/spells/BattleSpellsParams.h"
#include "battle/RoundActionsLog.h"
#include "retention/RetentionPolicy.h"

#include "params.h"

ExtraDamageEffect::ExtraDamageEffect(uint32_t id, ability::Type type, const Calculator *c, const policy_factory_t &p, bool use_full_value):
	BattleEffect(id, type, ability::Modifier::MODIFY_ATTACK, 0, p), calculator(c), is_negative(false), use_full_value(use_full_value)
{}

ExtraDamageEffect::~ExtraDamageEffect()
{
	delete this->calculator;
}

bool ExtraDamageEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();

	uint8_t extra = Sharps::get_sharp_times(this->get_ability(), card);
	int32_t damage = this->use_full_value ? card->get_damage() : card->get_base_damage();
	int32_t value = this->calculator->get(damage) * extra;

	if (value < 0)
		this->is_negative = true;

	bool changed = card->change_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id(), value);
	if (changed)
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});

	return changed;
}

bool ExtraDamageEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();
	card->revert_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id());

	ctx.log->effect_remove(combatant.get(), this->get_ability(), this->get_effect());

	return true;
}

bool ExtraDamageEffect::is_negative_for(const combatant_ptr_t &) const
{
	return this->is_negative;
}