#include "Buy.h"

namespace server
{

SERVER_PACKET_SOURCE(Buy)

Buy::Buy(Status status)
{
	this->add(static_cast<uint8_t>(status));
	this->write();
}

Buy::Buy(Status status, uint32_t good_id, uint32_t target_id, uint32_t gold_price, uint32_t souls_price, uint32_t data)
{
	this->add(static_cast<uint8_t>(status));
	this->add(good_id);
	this->add(target_id);
	this->add(gold_price);
	this->add(souls_price);
	this->add(data);
	this->write();
}

Buy::Buy(Status status, uint32_t good_id, uint32_t target_id, uint32_t gold_price, uint32_t souls_price, uint32_t data, const server::Group &data_group)
{
	this->add(static_cast<uint8_t>(status));
	this->add(good_id);
	this->add(target_id);
	this->add(gold_price);
	this->add(souls_price);
	this->add(data);
	this->add(&data_group);
	this->write();
}

}