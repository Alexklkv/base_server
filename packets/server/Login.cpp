#include "Login.h"

#include "Flags.h"

#include "../Boosters.h"
#include "../Decoration.h"
#include "../Equipment.h"
#include "../Friends.h"
#include "../Items.h"
#include "../Locations.h"
#include "../Statistics.h"
#include "../Totems.h"

namespace server
{

SERVER_PACKET_SOURCE(Login)

Login::Login(Status status)
{
	this->add(static_cast<uint8_t>(status));

	this->write();
}

Login::Login(Status status, uint32_t inner_id, uint32_t client_id, const char *tower,
	const Flags *flags,
	const Statistics *statistics, const Totems *totems, const Items *items,
	const Equipment *equipment, const Decoration *decoration, uint8_t slots,
	const Group &unread_messages_senders, uint32_t time_to_next_midnight,
	uint32_t vip_left, const Friends *friends)
{
	this->add(static_cast<uint8_t>(status));
	this->add(inner_id);
	this->add(client_id);
	this->add(tower);
	this->add(flags);
	statistics->write_winnings(this);
	this->add(totems);
	this->add(items);
	equipment->write_all(this);
	decoration->write_all(this);
	this->add(slots),
	this->add(&unread_messages_senders);
	this->add(time_to_next_midnight);
	this->add(vip_left);
	this->add(friends);

	this->write();
}

}