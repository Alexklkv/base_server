#pragma once

#include "server/Object.h"
#include "server/Writer.h"

struct Friend : public server::Object
{
	uint32_t friend_id;

	mutable bool saved;

	inline bool operator==(uint32_t friend_id) const
	{
		return (this->friend_id == friend_id);
	}

	void write(server::Writer *writer) const;
};