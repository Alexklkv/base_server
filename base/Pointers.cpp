#include "Pointers.h"
#include "Enum.h"
#include "Exception.h"

Pointers::Pointers()
{
	this->pointers.fill(0);
}

uint16_t Pointers::get(PointerID point) const
{
	if (enum_unwrap(point) >= this->pointers.size())
		throw Exception("Invalid id pointer");

	return this->pointers[point];
}

void Pointers::set(PointerID point, uint16_t value)
{
	if (enum_unwrap(point) >= this->pointers.size())
		throw Exception("Invalid id pointer");

	this->pointers[point] += value;
}