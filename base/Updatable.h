#pragma once

class Savable;

class Updatable
{
protected:
	Savable *owner;
	bool updated;

	void update();

	uint32_t get_owner() const;

public:
	explicit Updatable(Savable *owner);
	virtual ~Updatable();

	virtual bool save();
};