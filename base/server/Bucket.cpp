#include "Bucket.h"

#include <stdlib.h>
#include <string.h>

namespace server
{

Bucket::Bucket():
	data(nullptr), size(0)
{}

Bucket::~Bucket()
{
	if (this->data == nullptr)
		return;

	free(this->data);
}

const char* Bucket::get_data() const
{
	return this->data;
}

uint32_t Bucket::get_size() const
{
	return this->size;
}

void Bucket::resize(uint32_t size)
{
	if (size <= this->size)
		return;

	this->data = static_cast<char*>(realloc(this->data, size));
}

void Bucket::add(const void *data, uint32_t length)
{
	memcpy(this->data + this->size, data, length);
	this->size += length;
}

}