#pragma once

#include "BaseConfig.h"

#include "client/Group.h"
#include "client/Reader.h"

namespace client
{

class Group;

class Packet : public Reader
{
private:
	static uint16_t max_type;
	static const char **formats;

	BaseConfig::Protocol protocol;

	uint16_t type;
	uint32_t id;

	bool valid;

	uint32_t size;
	char *buffer;

	Group *group;

	template<typename T> T read();
	template<typename T> void fetch();

	bool parse(uint32_t id);

public:
	Packet(const char *buffer, uint32_t size, BaseConfig::Protocol protocol, uint32_t id);
	~Packet();

	static void init(const char **formats, uint16_t max_type);

	bool is_valid() const;
	uint16_t get_type() const;
	const void* get_data() const;
	size_t get_size() const;
	BaseConfig::Protocol get_protocol() const;
};

template<typename T> T Packet::read()
{
	uint16_t length = sizeof(T);

	if (this->size < length)
		throw "No data for T";

	T data = * (T *)(this->buffer);

	this->buffer += length;
	this->size -= length;

	return data;
}

template<typename T> void Packet::fetch()
{
	T data = this->read<T>();

	if (this->group != nullptr)
		this->group->add(data);
	else
		this->add(data);
}

}