#pragma once

#include "RetentionPolicy.h"

class ComboRetentionPolicy : public RetentionPolicy
{
	bool is_expired = false;

public:
	ComboRetentionPolicy();

	virtual bool combo_removal() override;
	virtual bool expired() const override;
};