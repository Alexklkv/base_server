#include "RatingsSizes.h"

namespace server
{

SERVER_PACKET_SOURCE(RatingsSizes)

RatingsSizes::RatingsSizes(const server::Group &ratings_sizes)
{
	this->add(&ratings_sizes);
	this->write();
}

}