#pragma once

#include "RetentionPolicy.h"

class TurnsRetentionPolicy : public RetentionPolicy
{
	uint32_t turns_left;

public:
	explicit TurnsRetentionPolicy(uint32_t turns_count);

	virtual bool end_turn() override;
	virtual bool expired() const override;
};