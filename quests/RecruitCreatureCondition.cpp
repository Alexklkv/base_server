#include "RecruitCreatureCondition.h"

namespace quests
{

RecruitCreatureCondition::RecruitCreatureCondition(BaseCard::Grade min_grade):
	min_grade(min_grade)
{}

QuestType RecruitCreatureCondition::type() const
{
	return RECRUIT_CREATURE;
}

bool RecruitCreatureCondition::compare(const Condition *condition) const
{
	if (!this->Condition::compare(condition))
		return false;

	return (static_cast<const RecruitCreatureCondition*>(condition)->min_grade >= this->min_grade);
}

}