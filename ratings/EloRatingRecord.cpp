#include "EloRatingRecord.h"

EloRatingRecord::EloRatingRecord():
	points(0)
{}

void EloRatingRecord::write(server::Writer *writer) const
{
	this->BaseRatingRecord::write(writer);
	writer->add(this->points);
}