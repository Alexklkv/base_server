#pragma once

#include "RetentionPolicy.h"

class ActionsRetentionPolicy : public RetentionPolicy
{
	uint32_t actions_left;

public:
	explicit ActionsRetentionPolicy(uint32_t actions_count);

	virtual bool end_action() override;
	virtual bool expired() const override;
};