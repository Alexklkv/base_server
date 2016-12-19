#pragma once

#include "Thread.h"

#include <concurrent_queue.h>

class BaseDatabase;

class Blocks : public Thread
{
	friend class BaseDatabase;

private:
	struct Block
	{
		uint8_t reason;
		uint8_t repeated;
		uint32_t judge;
		uint32_t target;
		uint32_t time;
	};

	typedef tbb::concurrent_queue<Block> blocks_t;

	blocks_t blocks;

	void save();

protected:
	void on_notify();

public:
	Blocks();
	~Blocks();

	void add(uint8_t reason, uint8_t repeated, uint32_t judge, uint32_t target);
};