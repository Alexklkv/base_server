#include "Writer.h"

#include "BaseConfig.h"
#include "BaseServer.h"
#include "Group.h"
#include "Object.h"

#include <string.h>

namespace server
{

static const uint16_t WRITER_INIT_SIZE = 256;

Writer::Writer():
	Writer(WRITER_INIT_SIZE)
{}

Writer::Writer(uint32_t start_size):
	max(start_size), bucket(new Bucket)
{
	this->bucket->resize(this->max);
}

Writer::~Writer()
{}

const char* Writer::get_data() const
{
	return this->bucket->data;
}

uint32_t Writer::get_size() const
{
	return this->bucket->size;
}

shared_ptr<Bucket> Writer::get_bucket() const
{
	return this->bucket;
}

void Writer::write(const void *data, uint32_t length)
{
	if (this->max < this->bucket->size + length)
	{
		while (this->max < this->bucket->size + length)
			this->max *= 2;

		this->bucket->resize(this->max);
	}

	this->bucket->add(data, length);
}

void Writer::add(const char *value)
{
	uint16_t length = static_cast<uint16_t>(strlen(value));

	this->write(&length, sizeof(length));
	this->write(value, length);

	uint8_t zero = 0;
	this->write(&zero, sizeof(zero));
}

void Writer::add(const char *value, uint32_t length)
{
	this->write(&length, sizeof(length));
	this->write(value, length);
}

void Writer::add(float value)
{
	this->write(&value, sizeof(value));
}

void Writer::add(uint64_t value)
{
	this->write(&value, sizeof(value));
}

void Writer::add(uint32_t value)
{
	this->write(&value, sizeof(value));
}

void Writer::add(uint16_t value)
{
	this->write(&value, sizeof(value));
}

void Writer::add(uint8_t value)
{
	this->write(&value, sizeof(value));
}

void Writer::add(const Object &object)
{
	this->add(&object);
}

void Writer::add(const Object *object)
{
	object->write(this);
}

void Writer::add(const Group *group, bool as_array)
{
	if (as_array)
	{
		uint32_t size = group->get_size() + sizeof(uint16_t);
		this->write(&size, sizeof(size));
	}

	uint16_t length = group->get_length();

	this->write(&length, sizeof(length));
	this->write(group->get_data(), group->get_size());
}

}