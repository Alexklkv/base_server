#pragma once

#include <inttypes.h>
#include <stddef.h>
#include <tuple>
#include <type_traits>

template<>
	struct std::make_unsigned<bool>
{
	typedef uint8_t type;
};

template<typename... Fields> class PackedTuple;

class PackedFields
{
public:
	template<typename... Values>
	PackedFields(Values... values):
		data(this->calculate<0>(0, values...))
	{}

	template<typename... Fields>
	static void unpack(uint64_t data, Fields&... fields)
	{
		unpack_fields<sizeof(data)>(data, fields...);
	}

	static uint64_t part(uint64_t data, size_t offset, size_t size)
	{
		data = data << ((sizeof(data) - offset) * 8);
		data = data >> ((sizeof(data) - size) * 8);

		return data;
	}

	const uint64_t data;

private:
	template<
		size_t OFFSET,
		typename First
	>
	static void unpack_fields(uint64_t data, First &field)
	{
		field = part(data, OFFSET, sizeof(First));
	}

	template<
		size_t OFFSET,
		typename First,
		typename... Fields
	>
	static void unpack_fields(uint64_t data, First &field, Fields&... fields)
	{
		static_assert(OFFSET > sizeof(First), "Not enough space unpack data in uint64_t");

		field = part(data, OFFSET, sizeof(First));
		unpack_fields<OFFSET - sizeof(First)>(data, fields...);
	}
	
	template<
		size_t OFFSET,
		typename First,
		typename... Values
	>
	uint64_t calculate(uint64_t data, First first, Values... values)
	{
		auto unsigned_first = static_cast<typename std::make_unsigned<First>::type>(first);
		data = (data << (sizeof(First) * 8)) | unsigned_first;

		return this->calculate<OFFSET + sizeof(First)>(data, values...);
	}

	template<
		size_t OFFSET,
		typename First
	>
	uint64_t calculate(uint64_t data, First first)
	{
		static_assert(OFFSET + sizeof(First) <= sizeof(uint64_t), "Not enough space for data in uint64_t");

		auto unsigned_first = static_cast<typename std::make_unsigned<First>::type>(first);

		data = (data << (sizeof(First) * 4));
		data = (data << (sizeof(First) * 4));
		return data | unsigned_first;
	}
};