#pragma once

#include "server/Object.h"
#include "server/Writer.h"

struct BaseRating : public server::Object
{
	uint32_t id;
	uint32_t value;

	BaseRating();

	virtual void write(server::Writer *writer) const;
};