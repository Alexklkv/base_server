#pragma once

#include "server/Group.h"
#include "server/Packet.h"

class Boosters;
class Decoration;
class Equipment;
class Flags;
class Friends;
class Items;
class Locations;
class Statistics;
class Totems;

namespace server
{

class Login : public Packet
{
	SERVER_PACKET_HEADER(Login)

public:
	enum Status : uint8_t
	{
		STATUS_SUCCESS,
		STATUS_FAILED,
		STATUS_EXIST,
		STATUS_BANNED,
		STATUS_WRONG_VERSION
	};

	Login(Status status);
	Login(Status status, uint32_t inner_id, uint32_t client_id, const char *tower,
		const Flags *flags,
		const Statistics *statistics, const Totems *totems, const Items *items,
		const Equipment *equipment, const Decoration *decoration, uint8_t slots,
		const Group &unread_messages_senders, uint32_t time_to_next_midnight,
		uint32_t vip_left, const Friends *friends);
};

}