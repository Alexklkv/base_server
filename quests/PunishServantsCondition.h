#pragma once

#include "Condition.h"

namespace quests
{

class PunishServantsCondition : public Condition
{
public:
	virtual QuestType type() const override;

};

}