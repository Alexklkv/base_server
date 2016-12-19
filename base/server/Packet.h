#pragma once

#include "Writer.h"

#include <stdarg.h>

#define SERVER_PACKET_HEADER(Class) \
	public:\
	static uint16_t type;\
	static bool logged;\
	static void init(uint16_t type, bool logged = true) {Class::type = type; Class::logged = logged;}\
	inline uint16_t get_type() const {return Class::type;}\
	inline bool need_logged() const {return Class::logged;}\

#define SERVER_PACKET_SOURCE(Class) \
	uint16_t Class::type = 0;\
	bool Class::logged = true;\

namespace server
{

class Packet : public Writer
{
	friend class BufferWrite;

protected:
	Packet();
	Packet(uint32_t start_size);

public:
	void write();

	virtual uint16_t get_type() const = 0;
	virtual bool need_logged() const = 0;
};

}