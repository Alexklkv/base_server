#pragma once

#include "BaseRatingRecord.h"

struct AsyncEloRatingRecord : public BaseRatingRecord
{
	uint16_t points;

	AsyncEloRatingRecord();

	void write(server::Writer *writer) const override;
};