#include "Storage.h"

#include "Gifts.h"

namespace server
{

namespace gifts
{

SERVER_PACKET_SOURCE(Storage)

Storage::Storage(const ::Gifts *gifts)
{
	this->add(gifts);
	this->write();
}

}

}