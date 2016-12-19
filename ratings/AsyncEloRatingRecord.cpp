#include "AsyncEloRatingRecord.h"

AsyncEloRatingRecord::AsyncEloRatingRecord():
	points(0)
{}

void AsyncEloRatingRecord::write(server::Writer *writer) const
{
	this->BaseRatingRecord::write(writer);
	writer->add(this->points);
}