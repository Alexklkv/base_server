#include "DefeatGreatBotCondition.h"

#include "Condition.h"

namespace quests
{

const std::set<uint8_t> DefeatGreatBotCondition::REQUIRED_LEVEL =
{
	33,
	35
};

DefeatGreatBotCondition::DefeatGreatBotCondition(BaseCard::Fraction fraction, uint8_t bot_level):
	BotCondition(fraction, bot_level)
{}

QuestType DefeatGreatBotCondition::type() const
{
	return DEFEAT_GREAT_BOT;
}

bool DefeatGreatBotCondition::compare(const Condition *condition) const
{
	if (!this->BotCondition::compare(condition))
		return false;

	return (REQUIRED_LEVEL.count(static_cast<const DefeatGreatBotCondition*>(condition)->bot_level) > 0);
}

}