#pragma once

class RetentionPolicy
{
public:
	enum Type : uint8_t
	{
		ACTIONS,
		PLACEMENT,
		COMBO,
		INFINITE,
		TURNS,
	};

	Type type;

	RetentionPolicy(Type type);
	virtual ~RetentionPolicy();

	virtual bool end_action();
	virtual bool end_turn();
	virtual bool move();
	virtual bool combo_removal();

	virtual bool expired() const = 0;
};