#include "Info.h"

#include "Flags.h"

namespace server
{

namespace admin
{

SERVER_PACKET_SOURCE(Info)

Info::Info(Status status)
{
	this->add(static_cast<uint8_t>(status));
	this->write();
}

Info::Info(Status status, uint32_t inner_id, const char *summoner_name, const char *tower_name, uint8_t sex,
		uint32_t gold, uint32_t souls, uint32_t respect, uint32_t experience, const Flags *flags,
		uint8_t main_characteristic, uint16_t education_state)
{
	this->add(static_cast<uint8_t>(status));
	this->add(inner_id);
	this->add(summoner_name);
	this->add(tower_name);
	this->add(sex);
	this->add(gold);
	this->add(souls);
	this->add(respect);
	this->add(experience);
	this->add(flags);
	this->add(main_characteristic);
	this->add(education_state);

	this->write();
}

}

}