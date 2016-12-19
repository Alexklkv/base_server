#include "TurnsRetentionPolicy.h"

#include "misc.h"

TurnsRetentionPolicy::TurnsRetentionPolicy(uint32_t turns_count):
	RetentionPolicy(RetentionPolicy::TURNS), turns_left(turns_count)
{}

bool TurnsRetentionPolicy::end_turn()
{
	this->turns_left = unsigned_substract(this->turns_left, 1);
	return this->expired();
}

bool TurnsRetentionPolicy::expired() const
{
	return (this->turns_left <= 0u);
}