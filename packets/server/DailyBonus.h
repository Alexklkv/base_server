#pragma once

#include "server/Packet.h"

namespace server
{

class DailyBonus : public Packet
{
	SERVER_PACKET_HEADER(DailyBonus)

public:
	DailyBonus(uint8_t current_day, uint8_t bonus, uint16_t data);
	DailyBonus(uint8_t current_day, uint8_t bonus, std::vector<uint16_t> data_t);

};

}