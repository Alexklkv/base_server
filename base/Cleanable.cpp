#include "Cleanable.h"

Cleanable::Cleanable():
	removed(false)
{}

void Cleanable::admin_clear()
{
	this->removed = true;
}

bool Cleanable::try_remove() const
{
	if (!this->removed)
		return false;

	this->removed = false;
	return true;
}