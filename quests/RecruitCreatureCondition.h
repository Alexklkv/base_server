#pragma once

#include "Condition.h"

#include "../BaseCard.h"

namespace quests
{

class RecruitCreatureCondition : public Condition
{
private:
	BaseCard::Grade min_grade;

public:
	RecruitCreatureCondition(BaseCard::Grade min_grade);

	QuestType type() const override;

	bool compare(const Condition *condition) const override;
};

}