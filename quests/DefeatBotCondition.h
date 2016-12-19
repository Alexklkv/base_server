#pragma once

#include "BotCondition.h"

#include "../QuestsParams.h"

namespace quests
{

class DefeatBotCondition : public BotCondition
{
	friend class ::QuestsParams;

private:
	uint8_t player_level;
	uint16_t location_id;

public:
	DefeatBotCondition(BaseCard::Fraction fraction);
	DefeatBotCondition(BaseCard::Fraction fraction, uint8_t bot_level, uint8_t player_level);
	DefeatBotCondition(uint16_t location_id);

	QuestType type() const override;

	bool compare(const Condition *condition) const override;
};

}