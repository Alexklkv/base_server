#pragma once

#include "RetentionPolicy.h"

class InfiniteRetentionPolicy : public RetentionPolicy
{
public:
	InfiniteRetentionPolicy();

	virtual bool expired() const override;
};