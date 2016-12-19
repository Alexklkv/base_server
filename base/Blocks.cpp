#include "Blocks.h"

#include "BaseConfig.h"
#include "BaseDatabase.h"
#include "BaseServer.h"

#include <time.h>

Blocks::Blocks():
	Thread("Blocks")
{}

Blocks::~Blocks()
{
	this->save();
}

void Blocks::add(uint8_t reason, uint8_t repeated, uint32_t judge, uint32_t target)
{
	Block block = {reason, repeated, judge, target, static_cast<uint32_t>(time(nullptr))};

	this->blocks.push(block);

	if (this->blocks.unsafe_size() >= config()->BLOCKS_SAVE_SIZE)
		this->notify();
}

void Blocks::save()
{
	base_database()->save_blocks(this);
}

void Blocks::on_notify()
{
	this->save();
}