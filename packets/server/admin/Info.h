#pragma once

#include "server/Packet.h"

class Flags;

namespace server
{

namespace admin
{

class Info : public Packet
{
	SERVER_PACKET_HEADER(Info)

public:
	enum Status : uint8_t
	{
		STATUS_SUCCESS = 0,
		STATUS_FAILED,
	};

	Info(Status status);
	Info(Status status, uint32_t inner_id, const char *name, const char *tower_name, uint8_t sex,
		uint32_t gold, uint32_t souls, uint32_t respect, uint32_t experience, const Flags *flags,
		uint8_t main_characteristic, uint16_t education_state);
};

}

}