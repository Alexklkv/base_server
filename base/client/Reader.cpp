#include "Reader.h"

#include "Group.h"

#include <stdlib.h>

namespace client
{

ReaderData::ReaderData(const char *data):
	S(data), type(TYPE_STRING)
{}

ReaderData::ReaderData(uint64_t data):
	L(data), type(TYPE_LONG)
{}

ReaderData::ReaderData(float data):
	F(data), type(TYPE_FLOAT)
{}

ReaderData::ReaderData(uint32_t data):
	I(data), type(TYPE_INT)
{}

ReaderData::ReaderData(uint16_t data):
	W(data), type(TYPE_WORD)
{}

ReaderData::ReaderData(uint8_t data):
	B(data), type(TYPE_BYTE)
{}

ReaderData::ReaderData(Group *data):
	G(data), type(TYPE_GROUP)
{}

ReaderData::ReaderData(const uint8_t *data):
	A(data), type(TYPE_BYTEARRAY)
{}

void ReaderData::release()
{
	switch (this->type)
	{
		case TYPE_GROUP:
			delete this->G;
			break;
		default:
			return;
	}
}

Reader::~Reader()
{
	for (auto &iter : this->data)
		iter.release();
}

bool Reader::has(size_t size) const
{
	return (this->data.size() > size);
}

size_t Reader::length() const
{
	return this->data.size();
}

}