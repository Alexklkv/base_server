#pragma once

#include "server/Packet.h"

class Summoner;

namespace server
{

class Arena : public Packet
{
	SERVER_PACKET_HEADER(Arena)

public:
	Arena(uint8_t status, Summoner *summoner, Summoner *opponent);
	Arena(uint8_t status, uint32_t first_player_id);
	Arena(uint8_t status);
};

}