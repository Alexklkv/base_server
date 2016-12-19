#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class Buy : public Packet
{
	SERVER_PACKET_HEADER(Buy)

public:
	enum Status : uint8_t
	{
		SUCCESS = 0,
		FAILED,
		PRICE_CHANGED,
		NO_BALANCE
	};

	Buy(Status status);
	Buy(Status status, uint32_t good_id, uint32_t target_id, uint32_t gold_price, uint32_t souls_price, uint32_t data);
	Buy(Status status, uint32_t good_id, uint32_t target_id, uint32_t gold_price, uint32_t souls_price, uint32_t data, const server::Group &data_group);
};

}