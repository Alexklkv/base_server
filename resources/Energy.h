#pragma once

#include "Resource.h"
#include "Updatable.h"

#include "server/Object.h"

#include <tuple>
#include <unordered_map>

class Player;

class Energy: public Resource, public server::Object
{
	friend class Database;

private:
	void set(float current_value, uint32_t last_update_time);
	Player *player;

	uint32_t last_update_time;

protected:
	virtual void set_value_increase_velocity(float value);

public:
	Energy(Player *player);

	virtual uint8_t type() const;
	virtual void renew();

	virtual bool use(float value);
	bool can_use(float value);
	void add(float value);
	void full_repair();

	void update_max_border();
	uint32_t get_last_update_time() const;
	float get_repair_speed() const;
	float get_max_border() const;

	void write(server::Writer *writer) const;
};
