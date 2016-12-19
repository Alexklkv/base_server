#include "BaseRating.h"

BaseRating::BaseRating():
	id(0), value(0)
{}

void BaseRating::write(server::Writer *writer) const
{
	writer->add(this->id);
	writer->add(this->value);
}