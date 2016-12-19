#include "BuyEquipment.h"
#include "../base/Log.h"
#include "../Player.h"
#include "../Equipment.h"
#include "../PricesParams.h"
#include "../LegendsServer.h"
#include "../EquipmentParams.h"

bool BuyEquipment::check(const Client* client, uint32_t, uint32_t data, const client::Group*)
{
	Equipment::Part part = Enum<Equipment::Part>::wrap(data & 0x000000FF);
	uint8_t type = (data >> 8);
	if (equipment_params()->get_part_data(part, type) == nullptr)
	{
		logger()->warning("Player %" PRIu32 " tried to buy wrong equipment part %" PRIu8 " type %" PRIu8, client->get_id(), part, type);
		return false;
	}
	if (client->player->equipment->has_part(part, type))
	{
		logger()->warning("Player %" PRIu32 " tried to buy equipment part %" PRIu8 " type %" PRIu8 " that he had already had", client->get_id(), part, type);
		return false;
	}
	logger()->debug("Player %" PRIu32 " wants to buy equipment part %" PRIu8 " type %" PRIu8, client->get_id(), part, type);
	return true;
}

void BuyEquipment::get_price(const Client*, uint32_t &gold_price, uint32_t &souls_price, uint32_t data, const client::Group*)
{
	Equipment::Part part = Enum<Equipment::Part>::wrap(data & 0x000000FF);
	uint8_t type = (data >> 8);
	gold_price = equipment_params()->get_part_data(part, type)->gold_price;
	souls_price = equipment_params()->get_part_data(part, type)->souls_price;
}

void BuyEquipment::give(Client* client, uint32_t, uint32_t& data, const client::Group*, server::Group&)
{
	Equipment::Part part = Enum<Equipment::Part>::wrap(data & 0x000000FF);
	uint8_t type = (data >> 8);
	client->player->add_equipment(part, type);
}