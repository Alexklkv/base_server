#include "ComboID.h"

#include <limits>

const ComboID ComboID::INVALID(std::numeric_limits<decltype(ComboID::id)>::max());

ComboID::ComboID(uint32_t id):
	id(id)
{}

ComboID::ComboID(const ComboID &other):
	ComboID(other.id)
{}

ComboID::ComboID(ComboID &&other):
	ComboID(other.id)
{}

ComboID ComboID::invalid()
{
	return INVALID;
}

bool ComboID::valid() const
{
	return *this != INVALID;
}

bool ComboID::operator==(const ComboID &other) const
{
	return this->id == other.id;
}

bool ComboID::operator!=(const ComboID& other) const
{
	return !(*this == other);
}

bool ComboID::operator<(const ComboID &other) const
{
	return this->id < other.id;
}