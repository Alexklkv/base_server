#pragma once

#include "server/Object.h"
#include "server/Writer.h"

struct Ban : public server::Object
{
	enum Type : uint8_t
	{
		TYPE_NONE,
		TYPE_GAG,
		TYPE_BAN
	};

	Type type;
	uint8_t reason;
	uint32_t judge;
	uint32_t finish;
	uint32_t start;

	Ban();

	void set(uint8_t reason, uint8_t repeated, uint32_t jugde);
	void set(Type type, uint8_t reason, uint32_t judge, uint32_t finish);

	bool is_active(Type type) const;
	uint32_t get() const;

	void write(server::Writer *writer) const;
};

struct BanTime
{
	Ban::Type type;
	uint32_t time;
	Ban::Type repeated_type;
	uint32_t repeated_time;
};