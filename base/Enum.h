#pragma once

#include <limits>
#include <type_traits>

template<typename T, typename = typename std::is_enum<T>::type>
struct Enum
{
	typedef T type;
	typedef typename std::underlying_type<T>::type underlying;

	static constexpr underlying underlying_max()
	{
		return std::numeric_limits<underlying>::max();
	}

	static constexpr underlying underlying_min()
	{
		return std::numeric_limits<underlying>::min();
	}

	static constexpr underlying unwrap(type value)
	{
		return static_cast<underlying>(value);
	}

	static constexpr type wrap(underlying value)
	{
		return static_cast<type>(value);
	}

	template<class Consumer>
	static void foreach(underlying from, type to, Consumer &&consumer)
	{
		underlying to_raw = unwrap(to);
		for (underlying raw = from; raw < to_raw; raw++)
		{
			type value = wrap(raw);
			consumer(value);
		}
	}
};

template<typename T>
typename Enum<T>::underlying enum_unwrap(T type)
{
	return Enum<T>::unwrap(type);
}

template<typename T, typename = typename std::is_enum<T>::type>
bool enum_invalid(T type)
{
	return type >= T::MAX;
}