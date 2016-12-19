#include "DatabasePacker.h"

DatabasePacker::DatabasePacker(const char *prefix, const char *postfix):
	is_empty(true), prefix(prefix), postfix(postfix)
{}

void DatabasePacker::internal_pack(bool)
{
	this->stream << ")";
}

std::string DatabasePacker::str() const
{
	if (this->empty())
		return "";

	return this->prefix + this->stream.str() + this->postfix;
}

bool DatabasePacker::empty() const
{
	return this->is_empty;
}

bool DatabasePacker::exists() const
{
	return !this->is_empty;
}

std::string DatabasePacker::description() const
{
	return this->prefix + std::string(" LIST ") + this->postfix;
}