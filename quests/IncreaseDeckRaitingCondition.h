#pragma once

#include "Condition.h"

namespace quests
{

class IncreaseDeckRaitingCondition : public Condition
{
public:
	QuestType type() const override;

};

}