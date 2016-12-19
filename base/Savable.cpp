#include "Savable.h"

#include "BaseServer.h"
#include "Saver.h"

Savable::Savable(uint32_t inner_id):
	inner_id(inner_id)
{
	this->saved = SAVED_ALL;
	this->saved_time = time(nullptr);
}

Savable::~Savable()
{}

void Savable::saved_remove(int what)
{
	volatile int saved_old, saved_new;

	do
	{
		saved_old = this->saved;
		saved_new = saved_old & ~what;
	}
	while ((this->saved.compare_and_swap(saved_new, saved_old) != saved_old));

	if (saved_old == SAVED_ALL)
		saver()->add(this);
}