#include "FightRandomEnemyCondition.h"

namespace quests
{

FightRandomEnemyCondition::FightRandomEnemyCondition()
{}

QuestType FightRandomEnemyCondition::type() const
{
	return FIGHT_RANDOM_ENEMY;
}

}