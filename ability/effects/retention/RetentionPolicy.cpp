#include "RetentionPolicy.h"

RetentionPolicy::RetentionPolicy(Type type):
	type(type)
{}
RetentionPolicy::~RetentionPolicy()
{}

bool RetentionPolicy::end_action()
{
	return false;
}

bool RetentionPolicy::end_turn()
{
	return false;
}

bool RetentionPolicy::move()
{
	return false;
}

bool RetentionPolicy::combo_removal()
{
	return false;
}