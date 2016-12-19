#include "CollectQuestItemCondition.h"

namespace quests
{

CollectQuestItemCondition::CollectQuestItemCondition(uint16_t item):
	item(item)
{}

QuestType CollectQuestItemCondition::type() const
{
	return COLLECT_QUEST_ITEMS;
}

bool CollectQuestItemCondition::compare(const Condition *condition) const
{
	if (!this->Condition::compare(condition))
		return false;

	const CollectQuestItemCondition *collect_item_conditon = dynamic_cast<const CollectQuestItemCondition*>(condition);

	return (collect_item_conditon->item == this->item);

}

}