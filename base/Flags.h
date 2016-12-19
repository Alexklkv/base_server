#pragma once

#include "Cleanable.h"
#include "NoCopy.h"

#include "server/Object.h"
#include "server/Writer.h"

#include "enums.h"

#include <array>

class BaseDatabase;

class Flags : public Cleanable, public server::Object, private NoCopy
{
	friend class BaseDatabase;

private:
	std::array<uint16_t, FlagType::FLAG_MAX_TYPE> flags;

public:
	Flags();

	void admin_clear() override;

	bool has(FlagType flag) const;
	uint16_t get(FlagType flag) const;
	void set(FlagType flag, uint16_t value);

	void write(server::Writer *writer) const;
};