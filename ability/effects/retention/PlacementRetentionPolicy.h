#pragma once

#include "RetentionPolicy.h"

class PlacementRetentionPolicy : public RetentionPolicy
{
	bool moved = false;

public:
	PlacementRetentionPolicy();
	virtual bool move() override;
	virtual bool expired() const override;
};