#pragma once

#include "Supports.h"

#include "server/Packet.h"

namespace server
{

namespace supports
{

class Request : public Packet
{
	SERVER_PACKET_HEADER(Request)

public:
	enum Status
	{
		SUCCESS = 0,
		FAILED
	};

	Request(Status status);
	Request(Status status, uint32_t assistant_id, const Supports::Key &key);
};

}

}