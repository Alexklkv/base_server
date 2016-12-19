#pragma once

#include "server/Object.h"
#include "server/Writer.h"

struct BaseRatingRecord : public server::Object
{
	uint32_t player_id;

	BaseRatingRecord();

	void write(server::Writer *writer) const override;
};