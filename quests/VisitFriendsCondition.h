#pragma once

#include "Condition.h"

namespace quests
{

class VisitFriendsCondition : public Condition
{
public:
	QuestType type() const override;

};

}