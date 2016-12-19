#include "IDGenerator.h"

IDGenerator::IDGenerator(uint32_t last_id)
{
	this->reset(last_id);
}

uint32_t IDGenerator::next()
{
	return this->next_id++;
}

void IDGenerator::reset(uint32_t last_id)
{
	this->next_id = last_id + 1;
}

void IDGenerator::grow_to(uint32_t last_id)
{
	if (this->next_id <= last_id)
		this->reset(last_id);
}