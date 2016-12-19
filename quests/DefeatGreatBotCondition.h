#pragma once

#include "BaseCard.h"				// BaseCard::Fraction
#include "BotCondition.h"			// BotCondition

#include "enums.h"

#include <set>

class Condition;

namespace quests
{

class DefeatGreatBotCondition : public BotCondition
{
	friend class QuestsParams;

public:
	static const std::set<uint8_t> REQUIRED_LEVEL;

	explicit DefeatGreatBotCondition(BaseCard::Fraction fraction, uint8_t bot_level = 0);

	QuestType type() const override;

	bool compare(const Condition *condition) const override;
};

}