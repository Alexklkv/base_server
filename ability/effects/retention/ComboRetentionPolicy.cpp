#include "ComboRetentionPolicy.h"

ComboRetentionPolicy::ComboRetentionPolicy():
	RetentionPolicy(RetentionPolicy::COMBO)
{}

bool ComboRetentionPolicy::combo_removal()
{
	this->is_expired = true;
	return true;
}

bool ComboRetentionPolicy::expired() const
{
	return this->is_expired;
}