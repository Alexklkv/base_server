#include "Group.h"

namespace server
{

Group::Group():
	length(0)
{}

void Group::next()
{
	this->length++;
}

uint16_t Group::get_length() const
{
	return this->length;
}

}