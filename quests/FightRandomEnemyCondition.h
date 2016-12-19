#pragma once

#include "Condition.h"

namespace quests
{

class FightRandomEnemyCondition : public Condition
{
public:
	FightRandomEnemyCondition();

	QuestType type() const override;
};

}