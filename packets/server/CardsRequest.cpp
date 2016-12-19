#include "CardsRequest.h"

#include "../Cards.h"

namespace server
{

SERVER_PACKET_SOURCE(CardsRequest)

CardsRequest::CardsRequest(CardRequestReason reason, Cards *cards)
{
	this->add(enum_unwrap(reason));
	this->add(cards);
	this->write();
}

}