#pragma once

#include "Condition.h"

namespace quests
{

class MakeGiftCondition : public Condition
{
public:
	QuestType type() const override;

};

}