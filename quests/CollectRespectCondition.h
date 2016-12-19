#pragma once

#include "Condition.h"

namespace quests
{

class CollectRespectCondition : public Condition
{
public:
	QuestType type() const override;

};

}