#include "PlacementRetentionPolicy.h"

PlacementRetentionPolicy::PlacementRetentionPolicy():
	RetentionPolicy(RetentionPolicy::PLACEMENT)
{}

bool PlacementRetentionPolicy::move()
{
	this->moved = true;
	return true;
}

bool PlacementRetentionPolicy::expired() const
{
	return this->moved;
}