#include "Flags.h"

#include "client/Group.h"
#include "server/Group.h"
#include "Enum.h"
#include "Exception.h"

Flags::Flags()
{
	this->flags.fill(0);
}

void Flags::admin_clear()
{
	Cleanable::admin_clear();
	this->flags.fill(0);
}

bool Flags::has(FlagType flag) const
{
	return (this->get(flag) != 0);
}

uint16_t Flags::get(FlagType flag) const
{
	if (enum_unwrap(flag) >= this->flags.size())
		throw Exception("Invalid flag type");

	return this->flags[flag];
}

void Flags::set(FlagType flag, uint16_t value)
{
	if (enum_unwrap(flag) >= this->flags.size())
		throw Exception("Invalid flag type");

	this->flags[flag] = value;
}

void Flags::write(server::Writer *writer) const
{
	server::Group group;

	for (size_t flag = 0; flag < flags.size(); flag++)
	{
		group.add(this->flags[flag]);
		group.next();
	}

	writer->add(&group);
}