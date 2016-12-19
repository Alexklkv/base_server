#include "Energy.h"

#include "Client.h"
#include "LegendsServer.h"
#include "Player.h"

#include "server/Writer.h"
#include "server/Group.h"
#include "params.h"

Energy::Energy(Player *player)
{
	this->repair_speed = Config::ENERGY_REPAIR_SPEED;
	this->border = energy::LEVEL_ENERGY[1];

	this->player = player;
	this->value = this->get_max_border();
	this->value_increase_velocity = this->get_repair_speed();
	this->last_update_time = 0;
}

uint8_t Energy::type() const
{
	return static_cast<uint8_t>(Resource::ENERGY);
}

void Energy::renew()
{
	uint32_t old_update_time = this->last_update_time;
	this->last_update_time = time(nullptr);

	if (this->value >= this->get_max_border())
		return;

	float delay = static_cast<float> (this->last_update_time - old_update_time);

	this->value += delay * this->get_repair_speed();

	if (this->value > this->get_max_border())
	{
		this->value = this->get_max_border();
		this->set_value_increase_velocity(0);
	}

	if (this->value < 0)
		this->value = 0;

	this->player->saved_remove(Player::SAVED_DATA);
}

bool Energy::use(float value)
{
	bool use_result = Resource::use(value);

	if (use_result)
		this->set_value_increase_velocity(this->repair_speed);

	return use_result;
}

bool Energy::can_use(float value)
{
	this->renew();

	if (this->value < value)
		return false;

	return true;
}

void Energy::add(float value)
{
	this->renew();

	this->value += value;

	if (this->value >= this->get_max_border())
	{
		this->set_value_increase_velocity(0);
		this->value = this->get_max_border();
	}
	else
		this->set_value_increase_velocity(this->get_repair_speed());
}

void Energy::full_repair()
{
	this->renew();

	if (this->value < this->get_max_border())
	{
		this->value = this->get_max_border();
		this->set_value_increase_velocity(0);
	}
}

void Energy::update_max_border()
{
	uint8_t level = this->player->get_level();
	this->border = energy::LEVEL_ENERGY[level];
}

uint32_t Energy::get_last_update_time() const
{
	return this->last_update_time;
}

float Energy::get_repair_speed() const
{
	return this->repair_speed;
}

float Energy::get_max_border() const
{
	return this->border;
}

void Energy::set_value_increase_velocity(float value)
{
	this->value_increase_velocity = value;
	//this->player->event(Client::EVENT_ENERGY);
}

void Energy::set(float current_value, uint32_t last_update_time)
{
	this->value = current_value;
	this->last_update_time = last_update_time;

	if (this->value < this->get_max_border())
		this->value_increase_velocity = this->repair_speed;
}

void Energy::write(server::Writer* writer) const
{
	writer->add(this->get());
}
