#include "Friend.h"

#include "server/Writer.h"

void Friend::write(server::Writer *writer) const
{
	writer->add(this->friend_id);
}