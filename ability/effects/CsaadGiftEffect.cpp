#include "CsaadGiftEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

CsaadGiftEffect::CsaadGiftEffect(uint32_t id, ability::Type type, const policy_factory_t &policy):
	BattleEffect(id, type, ability::Modifier::MODIFY_ATTACK, 0, policy)
{}

bool CsaadGiftEffect::on_target_after(CardAttackContext &ctx) const
{
	if (ctx.target->is_dead())
		return false;

	auto card = ctx.target->get_card();

	float percent = card->get_injuires() / card->get_health();
	uint16_t value = floor(card->get_damage() * percent);
	int16_t old_value = card->revert_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id());

	if (!card->change_extra(BaseCard::ExtraType::ATTACK_DAMAGE, this->get_id(), value + old_value))
		return false;

	ctx.field->write_effect(this, ctx.target, {{ctx.target->object_id(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), int16_t(value), ability::Duration::INFINITE)}});
	return true;
}