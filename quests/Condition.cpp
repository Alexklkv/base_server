#include "Condition.h"

namespace quests
{

bool Condition::compare(const Condition *other) const
{
	return (this->type() == other->type());
}

}