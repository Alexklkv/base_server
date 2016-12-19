#pragma once

class Cleanable
{
protected:
	mutable bool removed;

public:
	Cleanable();
	virtual ~Cleanable() = default;

	virtual void admin_clear();
	bool try_remove() const;
};