#pragma once

#include "Condition.h"

namespace quests
{

class SacrificeCardCondition : public Condition
{
public:
	QuestType type() const override;

};

}