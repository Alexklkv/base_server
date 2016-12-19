#include "ExtictionEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"
#include "LegendsServer.h"

#include "battle/RoundActionsLog.h"
#include "retention/RetentionPolicy.h"

#include "params.h"

ExtictionEffect::ExtictionEffect(uint32_t id, ability::Type type, const Calculator *calculator, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_ATTACK, 0, policy), calculator(calculator)
{}

ExtictionEffect::~ExtictionEffect()
{
	delete this->calculator;
}

bool ExtictionEffect::on_self_round_start(RoundContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	auto card = combatant->get_card();

	if (card->get_damage() == 0)
		return false;

	card->revert_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id());

	float delta_value = this->calculator->get(card->get_damage());
	int32_t value = std::round(delta_value * card->get_round());

	bool changed = card->change_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id(), value);
	if (changed)
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});

	return changed;
}
