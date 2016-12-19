#pragma once

#include <cstdint>
#include <memory>
#include <vector>

struct CardData
{
	typedef std::vector<std::unique_ptr<CardData>> cards_data_t;

	uint16_t id;
	uint16_t base_health;
	uint16_t base_damage;

	uint16_t extra_health;
	uint16_t extra_damage;

	CardData(uint16_t id, uint16_t base_health, uint16_t base_damage, uint16_t extra_health, uint16_t extra_damage):
		id(id), base_health(base_health), base_damage(base_damage), extra_health(extra_health), extra_damage(extra_damage)
	{}

	uint16_t get_health() const {
		return this->base_health + this->extra_health;
	}

	uint16_t get_damage() const {
		return this->base_damage + this->extra_damage;
	}
};