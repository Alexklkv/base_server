#include "Updatable.h"

#include "Savable.h"

Updatable::Updatable(Savable *owner):
	owner(owner), updated(false)
{}

Updatable::~Updatable()
{}

void Updatable::update()
{
	this->updated = true;
	this->owner->saved_remove(Savable::SAVED_OTHER);
}

bool Updatable::save()
{
	if (!this->updated)
		return false;

	this->updated = false;
	return true;
}

uint32_t Updatable::get_owner() const
{
	return this->owner->inner_id;
}