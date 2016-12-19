#include "Resource.h"

#include "Log.h"

#include <chrono>
#include <unistd.h>

Resource::Resource() : value(0.0), repair_speed(0.1), border(100),
	update_time(std::chrono::steady_clock::now()), repair_delay(0), repair_delay_stayed(0),
	value_increase_velocity_changed(true), value_increase_velocity(0)
{}

Resource::~Resource()
{}

float Resource::get_value_increase_velocity()
{
	this->value_increase_velocity_changed = false;
	return this->value_increase_velocity;
}

float Resource::get() const
{
	return this->value;
}

bool Resource::use(float value)
{
	this->renew();

	if (this->value >= value) {
		this->value -= value;

		return true;
	}

	return false;
}

bool Resource::is_value_increase_velocity_changed() const
{
	return this->value_increase_velocity_changed;
}

void Resource::set_value_increase_velocity(float value)
{
	this->value_increase_velocity_changed = true;
	this->value_increase_velocity = value;
}
