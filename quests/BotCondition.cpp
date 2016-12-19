#include "BotCondition.h"

namespace quests
{

BotCondition::BotCondition(BaseCard::Fraction fraction, uint8_t bot_level):
	fraction(fraction), bot_level(bot_level)
{}

bool BotCondition::compare(const Condition *condition) const
{
	if (!this->Condition::compare(condition))
		return false;

	return (this->fraction == static_cast<const BotCondition*>(condition)->fraction);
}

}