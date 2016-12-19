#include "InfiniteRetentionPolicy.h"

InfiniteRetentionPolicy::InfiniteRetentionPolicy():
	RetentionPolicy(RetentionPolicy::INFINITE)
{}

bool InfiniteRetentionPolicy::expired() const
{
	return false;
}