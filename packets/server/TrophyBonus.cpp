#include "TrophyBonus.h"

namespace server
{

SERVER_PACKET_SOURCE(TrophyBonus)

TrophyBonus::TrophyBonus(TrophyType trophy, uint32_t amount)
{
	this->add(static_cast<uint8_t>(trophy));
	this->add(amount);

	this->write();
}

}