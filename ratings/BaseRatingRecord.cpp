#include "BaseRatingRecord.h"

BaseRatingRecord::BaseRatingRecord():
	player_id(0)
{}

void BaseRatingRecord::write(server::Writer *writer) const
{
	writer->add(this->player_id);
}