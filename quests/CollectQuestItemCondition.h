#pragma once

#include "Condition.h"

namespace quests
{

class CollectQuestItemCondition : public Condition
{
private:
	uint16_t item;

public:
	CollectQuestItemCondition(uint16_t item);

	QuestType type() const override;

	bool compare(const Condition *condition) const override;
};

}