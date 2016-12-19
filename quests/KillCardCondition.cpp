#include "KillCardCondition.h"

#include "../BaseCardParams.h"

namespace quests
{

KillCardCondition::KillCardCondition(CardMask &mask):
	mask(mask), card_type(static_cast<uint16_t>(-1)), location_id(0)
{}

KillCardCondition::KillCardCondition(const ICard *card):
	mask(CardMask::create(card)), card_type(static_cast<uint16_t>(-1)), location_id(0)
{}

KillCardCondition::KillCardCondition(uint16_t card_type, uint16_t location_id):
	mask(CardMask().set(BaseCard::NONE)), card_type(card_type), location_id(location_id)
{}

QuestType KillCardCondition::type() const
{
	return KILL_CARD;
}

bool KillCardCondition::compare(const Condition *condition) const
{
	if (!this->Condition::compare(condition))
		return false;

	const KillCardCondition *kill_card_condition = dynamic_cast<const KillCardCondition*>(condition);

	if (this->location_id != 0 && kill_card_condition->location_id != this->location_id)
		return false;

	if (this->card_type != static_cast<uint16_t>(-1))
		return (kill_card_condition->card_type == this->card_type);

	return this->mask.check_match(dynamic_cast<const KillCardCondition*>(condition)->mask);
}

}