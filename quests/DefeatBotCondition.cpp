#include "DefeatBotCondition.h"

namespace quests
{

DefeatBotCondition::DefeatBotCondition(BaseCard::Fraction fraction):
	BotCondition(fraction), player_level(0), location_id(0)
{}

DefeatBotCondition::DefeatBotCondition(BaseCard::Fraction fraction, uint8_t bot_level, uint8_t player_level):
	BotCondition(fraction, bot_level), player_level(player_level), location_id(0)
{}

DefeatBotCondition::DefeatBotCondition(uint16_t location_id):
	BotCondition(BaseCard::MAX_FRACTION), player_level(0), location_id(location_id)
{}

QuestType DefeatBotCondition::type() const
{
	return DEFEAT_BOT;
}

bool DefeatBotCondition::compare(const Condition *condition) const
{
	if (!this->BotCondition::compare(condition))
		return false;

	const DefeatBotCondition *defeat_bot_conditon = dynamic_cast<const DefeatBotCondition*>(condition);

	if (location_id != 0)
		return (defeat_bot_conditon->location_id == this->location_id);

	return (defeat_bot_conditon->player_level >= this->bot_level);

}

}