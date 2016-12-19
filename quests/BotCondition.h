#pragma once

#include "Condition.h"				// Condition

#include "BaseCard.h"				// BaseCard::Fraction

namespace quests
{

class BotCondition : public Condition
{
private:
	BaseCard::Fraction fraction;

protected:
	uint8_t bot_level;

	explicit BotCondition(BaseCard::Fraction fraction, uint8_t bot_level = 0);

public:
	bool compare(const Condition *condition) const override;
};

}