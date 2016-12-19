#include "DailyBonus.h"

namespace server
{

SERVER_PACKET_SOURCE(DailyBonus)

DailyBonus::DailyBonus(uint8_t current_day, uint8_t bonus, uint16_t data)
{
	this->add(current_day);
	this->add(bonus);
	this->add(data);
	this->write();
}

DailyBonus::DailyBonus(uint8_t current_day, uint8_t bonus, std::vector<uint16_t> data_t)
{
	this->add(current_day);
	this->add(bonus);
	for(uint16_t data: data_t)
		this->add(data);
	this->write();
}

}