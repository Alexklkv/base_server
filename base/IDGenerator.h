#pragma once

#include "NoCopy.h"

class IDGenerator : private NoCopy
{
	uint32_t next_id;

public:
	explicit IDGenerator(uint32_t last_id = 0);

	uint32_t next();
	void reset(uint32_t last_id);
	void grow_to(uint32_t last_id);
};