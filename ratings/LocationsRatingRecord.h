#pragma once

#include "BaseRatingRecord.h"

struct LocationsRatingRecord : public BaseRatingRecord
{
	uint16_t location_id;
	uint32_t points;

	LocationsRatingRecord();

	void write(server::Writer *writer) const override;
};