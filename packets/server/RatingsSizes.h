#pragma once

#include "server/Group.h"
#include "server/Packet.h"

namespace server
{

class RatingsSizes : public Packet
{
	SERVER_PACKET_HEADER(RatingsSizes)

public:
	RatingsSizes(const server::Group &ratings_sizes);

};

}