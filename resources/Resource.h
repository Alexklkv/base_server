#pragma once

#include <chrono>

class Resource
{
public:
	enum ResourceType : uint8_t {
		ENERGY = 0,
	};

	Resource();
	virtual ~Resource();
	virtual void renew() = 0;
	virtual uint8_t type() const = 0;
	bool is_value_increase_velocity_changed() const;
	float get_value_increase_velocity();
	virtual float get() const;
	virtual bool use(float value);

protected:
	float value;
	float repair_speed;
	float border;
	std::chrono::steady_clock::time_point update_time;
	float repair_delay;
	float repair_delay_stayed;

	virtual void set_value_increase_velocity(float value);

	bool value_increase_velocity_changed;
	float value_increase_velocity;
};
