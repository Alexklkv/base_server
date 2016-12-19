#include "LocationsRatingRecord.h"

LocationsRatingRecord::LocationsRatingRecord():
	location_id(0), points(0)
{}

void LocationsRatingRecord::write(server::Writer *writer) const
{
	this->BaseRatingRecord::write(writer);
	writer->add(this->location_id);
	writer->add(this->points);
}