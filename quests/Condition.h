#pragma once

#include "enums.h"

namespace quests
{

class Condition
{
public:
	virtual ~Condition() = default;

	virtual QuestType type() const = 0;

	virtual bool compare(const Condition *other) const;
};

}