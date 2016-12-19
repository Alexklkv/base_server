#pragma once

#include "BaseRatingRecord.h"

struct EloRatingRecord : public BaseRatingRecord
{
	uint16_t points;

	EloRatingRecord();

	void write(server::Writer *writer) const override;
};