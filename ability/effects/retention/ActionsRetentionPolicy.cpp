#include "ActionsRetentionPolicy.h"

#include "misc.h"

ActionsRetentionPolicy::ActionsRetentionPolicy(uint32_t actions_count):
	RetentionPolicy(RetentionPolicy::ACTIONS), actions_left(actions_count)
{}

bool ActionsRetentionPolicy::end_action()
{
	this->actions_left = unsigned_substract(this->actions_left, 1);
	return this->expired();
}

bool ActionsRetentionPolicy::expired() const
{
	return (this->actions_left <= 0u);
}