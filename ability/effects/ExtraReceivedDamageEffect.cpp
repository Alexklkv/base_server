#include "ExtraReceivedDamageEffect.h"

#include "BattleField.h"
#include "CardHandler.h"
#include "DataPacker.h"

#include "battle/RoundActionsLog.h"

ExtraReceivedDamageEffect::ExtraReceivedDamageEffect(uint32_t id, ability::Type type, BaseCard::Range range, BaseCard::Fraction fraction, int8_t value, const policy_factory_t &p):
	BattleEffect(id, type, ability::Modifier::NONE_MODIFIER, 0, p), range(range), fraction(fraction), applied_type(BaseCard::ExtraType::MAX_EXTRA), value(value)
{}

BaseCard::ExtraType ExtraReceivedDamageEffect::convert_range(BaseCard::Range range)
{
	BaseCard::ExtraType type_range = BaseCard::ExtraType::MAX_EXTRA;

	switch (range)
	{
		case BaseCard::Range::NONE:
			type_range = BaseCard::ExtraType::RECEIVED_DAMAGE;
			break;
		case BaseCard::Range::MELEE:
			type_range = BaseCard::ExtraType::RECEIVED_DAMAGE_MELEE;
			break;
		case BaseCard::Range::DISTANT:
			type_range = BaseCard::ExtraType::RECEIVED_DAMAGE_DISTANT;
			break;
		case BaseCard::Range::FLYING_CREATURE:
			type_range = BaseCard::ExtraType::RECEIVED_DAMAGE_FLYING_CREATURE;
			break;

		default:
			break;
	}

	return type_range;
}

BaseCard::ExtraType ExtraReceivedDamageEffect::convert_fraction(BaseCard::Fraction fraction)
{
	BaseCard::ExtraType type_fraction = BaseCard::ExtraType::MAX_EXTRA;

	switch (fraction)
	{
		case BaseCard::Fraction::DEAD_LEGION:
			type_fraction = BaseCard::ExtraType::RECEIVED_DAMAGE_DEAD_LEGION;
			break;
		case BaseCard::Fraction::COMMUNE:
		case BaseCard::Fraction::FRATERNITY:
		case BaseCard::Fraction::NORTH:
		case BaseCard::Fraction::NEUTRAL:
			type_fraction = BaseCard::ExtraType::RECEIVED_DAMAGE;
			break;
		default:
			break;
	}

	return type_fraction;
}

bool ExtraReceivedDamageEffect::on_before_application(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	BaseCard::ExtraType type_fraction = convert_fraction(this->fraction);
	BaseCard::ExtraType type_range = convert_range(this->range);

	this->applied_type = (type_fraction == BaseCard::ExtraType::RECEIVED_DAMAGE) ? type_range : type_fraction;

	if (combatant->get_card()->change_extra(this->applied_type, this->get_id(), this->value))
	{
		ctx.targets_log.push_back({ctx.owner.get(), DataPacker().pack(ability::Action::ADD_EFFECT, this->get_effect(), (int16_t)value, ability::Duration::INFINITE)});
		return true;
	}

	return false;
}

bool ExtraReceivedDamageEffect::on_after_removal(StatsContext &ctx) const
{
	auto combatant = ctx.owner;
	if (!combatant->is_card())
		return false;

	combatant->get_card()->revert_extra(this->applied_type, this->get_id());
	ctx.log->effect_remove(combatant.get(), this->get_ability(), this->get_effect());

	return true;
}